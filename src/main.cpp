#include "hypothesis.h"
#include <bits/stdc++.h>


using namespace std;

vector<Hypothesis> general,specific;										// vector of classes for general and specific boundary
pair< vector<Hypothesis>, vector<Hypothesis> > boundary[8];
vector< vector <string> > input_data[8];
vector< vector< string> > input_attr = readAttr();  		// function to read the input data 7 times for each class
const int num_attr = 16;

void find_target(int idx)																			// function to find target hypothesis
{
	general.clear();	specific.clear();
	general.push_back(Hypothesis(num_attr,match_all));					// initial general boundary
	specific.push_back(Hypothesis(num_attr,match_none)); 				// initial specific boundary

	for(vector<vector<string> >:: iterator it=input_data[idx].begin();it!=input_data[idx].end();it++)
	{
		vector<string> instance = *it,temp;

		for(int i=0;i<instance.size();i++)	if(i!=0 && i!=instance.size()-1)	temp.push_back(instance[i]);
		int target_val = atoi((instance[instance.size()-1]).c_str());				// storing the target value

		if(target_val==1)																				// if the example is positive
		{
			vector<Hypothesis> temp_hyp;

			for(int i=0;i<general.size();i++)
				if(general[i].isSatisfy(temp) == target_val)				// checking for consistency with training example
					temp_hyp.push_back(general[i]);

			general.clear();
			general=temp_hyp;
			temp_hyp.clear();

			for(int i=0;i<specific.size();i++)
			{
				if(specific[i].isSatisfy(temp)== target_val)
					temp_hyp.push_back(specific[i]);
				else
				{
					vector<string> min_gen;
					for(int j=0;j<num_attr;j++)
					{
						string s= specific[i][j];
						if(s == match_none)		s=temp[j];
						else if(s!=temp[j])		s="?";								// generalising the specific boundary
						min_gen.push_back(s);
					}

					int flag=0;
					if(Hypothesis(num_attr,min_gen).isSatisfy(temp)== target_val)
					{
						for(int j=0;j<general.size();j++)
							if(general[j] > Hypothesis(num_attr,min_gen))
							{
								flag=1;
								break;
							}
					}
					if(flag==1)		temp_hyp.push_back(Hypothesis(num_attr,min_gen));

			}
		}
			specific.clear();
			specific = temp_hyp;
		}

		else																							// if the example is negative
		{
			vector<Hypothesis> temp_hyp;

			for(int i=0;i<specific.size();i++)
				if(specific[i].isSatisfy(temp) == target_val)
					temp_hyp.push_back(specific[i]);

			specific.clear();
			specific = temp_hyp;
			temp_hyp.clear();

			for(int i=0;i<general.size();i++)
			{
				if(general[i].isSatisfy(temp) == target_val)
					temp_hyp.push_back(general[i]);
				else																					// specializing the general boundary
				{
					vector<Hypothesis> temp_hyp_2;
					vector<string> min_spf;
					for(int j=0;j<num_attr;j++)		min_spf.push_back(general[i][j]);

					for(int j=0;j<num_attr;j++)			//minimum specialization of the inconsistent hypothesis
					{
						if(min_spf[j]==match_all)
						{
							string s= temp[j];
							for(int k=0;k<input_attr[j].size();k++)
							{
								if(input_attr[j][k]!=s)
								{
									min_spf[j]=input_attr[j][k];
									temp_hyp_2.push_back(Hypothesis(num_attr,min_spf));
								}
							}
							min_spf[j]=match_all;
						}

						else
						{
							string s= min_spf[j];
							min_spf[j]=match_none;
							temp_hyp_2.push_back(Hypothesis(num_attr,min_spf));
							min_spf[j]=s;
						}
					}
					for(int j=0;j<temp_hyp_2.size();j++)
					{
						if(temp_hyp_2[j].isSatisfy(temp) == target_val)		// checking if newly generated hypothesis is consistent
							{
								int flag=0;
								for(int k=0;k<specific.size();k++)
							{
									if(specific[k] < temp_hyp_2[j])
									{
										flag=1;
										break;
									}
							}
							if(flag==1)	temp_hyp.push_back(temp_hyp_2[j]);
						}
					}
				}
			}
			general.clear();
			for(int i=0;i<temp_hyp.size();i++)
			{
				int flag=1;
				for(int j=0;j<temp_hyp.size();j++)
				{
					if(temp_hyp[i]<temp_hyp[j])			// checking if any general hypothesis is less general than any other general hypothesis
					{
						flag=0;
						break;
					}
				}
				if(flag==1)	general.push_back(temp_hyp[i]);
			}
		}
	}
	boundary[idx]= make_pair(specific,general);		// inserting the pair of boundaries
}


int main()
{
	for(int i=1;i<8;i++)	input_data[i]=readData();						// reading the data 7 times
	for(int i=1;i<8;i++)
	{
		for(vector<vector<string> >:: iterator it=input_data[i].begin();it!=input_data[i].end();it++)
		{
			int z= atoi(((*it)[(*it).size()-1]).c_str());
			if(z == i)
				(*it)[(*it).size()-1]="1";										// changing the target value for each class
			else (*it)[(*it).size()-1]="0";									// for easier computation
		}
	}
	for(int i=1;i<8;i++)
	{
		find_target(i);																		// function to generate the boundaries
		cout<<"Specific Hypothesis of version space "<<i<<endl;
		if(specific.size()==0)		cout<<"No specific boundary";
		else for(int i=0;i<specific.size();i++)	cout<<specific[i]<<" ";
		cout<<endl;
	  cout<<"General Hypothesis of version space "<<i<<endl;
		if(general.size()==0)		cout<<"No general boundary";
		else for(int i=0;i<general.size();i++)		cout<<general[i]<<" ";
		cout<<endl<<endl<<endl;
	}
	return 0;
}
