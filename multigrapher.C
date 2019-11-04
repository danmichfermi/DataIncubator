#include <iostream>
#include <string>

bool numbercheck(const string& s)
{
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void multigrapher(){

//Stylistic Items
TCanvas c1;
TStyle* mcStyle = new TStyle("Style","");
mcStyle->SetOptStat(0);
mcStyle->SetOptTitle(0);
mcStyle->SetOptDate(0);
mcStyle->SetCanvasColor(0); // canvas...
mcStyle->SetCanvasBorderMode(0);
mcStyle->SetCanvasBorderSize(0);
mcStyle->SetPadBottomMargin(0.1); //margins...
mcStyle->SetPadTopMargin(0.1);
mcStyle->SetPadLeftMargin(0.1);
mcStyle->SetPadRightMargin(0.1);
mcStyle->SetPadGridX(0); // grids, tickmarks
mcStyle->SetPadGridY(0);
mcStyle->SetPadTickX(1);
mcStyle->SetPadTickY(1);
gROOT->SetStyle("Style");

//Derived State Lists
string statelist[20]={"LA",
"TX",
"FL",
"NJ",
"NY",
"NC",
"PA",
"MS",
"IL",
"CA",
"MO",
"VA",
"SC",
"MA",
"CT",
"WV",
"OH",
"KY",
"MD",
"GA"};
int stateclaims[20] ={
456437,
370772,
294700,
192509,
169250,
101099,
73008,
62422,
51554,
50191,
49606,
48977,
45686,
34344,
28093,
27183,
27100,
24249,
23767,
21360};

//initialize plots
	int count[20]={0};
    ifstream  poldata("openFEMA_policies20190630_01.csv");
    string line;
    TH1F* histclaim = new TH1F("Claims","Normalized Claims and Policy Versus Year", 47, 1972, 2019);
    TH1F* histpol = new TH1F("Policies","Claims Versus Year", 47, 1972, 2019);
    TH1F *hist_bar= new TH1F("Loc","States and Claim/Policy Ratio",20,0,20);
    
    //specialized CSV reader
    while(std::getline(poldata,line))
    {
    	stringstream lineStream(line);
        string segment; 	
        int counter=0;	
        while(std::getline(lineStream,segment,',')){
        	counter++;
        	if(counter==32){
        		stringstream segmentStream(segment);
        		string doom;
        		std::getline(segmentStream,doom,'-');
        		if(numbercheck(doom)){
        			histpol->Fill(stoi(doom));
        		}
        	}
        	if (counter==37)
        	{
        	  	for (int i = 0; i < 20; ++i)
        	   	{
   					if (statelist[i].compare(segment)==0)
   					{
   						count[i]+=1;
   					}
   	    	   	}

        	}    
        }
    }
    poldata.close();
    string newlines;
    ifstream  claimdata("openFEMA_claims20190630.csv");
    while(std::getline(claimdata,newlines,'\n'))
    {
    	stringstream lineStream(newlines);
        string segment; 	
        int counter=0;	
        while(getline(lineStream,segment,','))
        {
        	counter++;
        	if(counter==37){
        		//cout<<segment<<endl;
        		if(numbercheck(segment)){
        			histclaim->Fill(stoi(segment));
        		}
        	}
        }
    }

    //actual plotting
    histclaim->Draw();
    histclaim->GetXaxis()->SetTitle("Year");
    histclaim->GetYaxis()->SetTitle("Normalized Count of Claims/Policies");
	histclaim->SetMarkerColor(12);
	histclaim->SetMarkerStyle(21);
  	histclaim->SetMarkerSize(1);

    histpol->Draw("same");
	histpol->SetMarkerColor(4);
	histpol->SetMarkerStyle(21);
  	histclaim->SetMarkerSize(1);

    //cout<<(histclaim->Integral())<<endl;
    //   	cout<<(histpol->Integral())<<endl;
   	histclaim->Scale(1.0/(histclaim->Integral()));
   	histpol->Scale(1.0/(histpol->Integral()));
    TLegend *legend = new TLegend(.67,.75,.87,.85);
    legend->AddEntry("Claims","Normalized Claims");
    legend->AddEntry("Policies","Normalized Policies");
    legend->Draw();
   	c1.Update();
   	c1.SaveAs("Claim_Policy_Time_Data.png");

   	c1.SetBottomMargin(0.15);
   	for(int i=0; i<20; i++){
   		hist_bar->Fill((float)i+0.5,(float)stateclaims[i]/((float) count[i]));
   		hist_bar->GetXaxis()->SetBinLabel(i+1, statelist[i].c_str());
   	}
   	hist_bar->Draw("BAR");
   	hist_bar->GetXaxis()->SetTitle("Highest Claim Count States Ordered by Claims");
   	hist_bar->GetYaxis()->SetTitle("State Claims/Policies");
   	c1.SaveAs("States_ClaimsPolicies.png");

}

//Old Code 11/3

/*double x[]={1998,2000,2001,2002,2003,2004,2005,2006,2007,2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019};

double y[] = {0,
0,
0,
0,
0,
0,
0,
0,
2,
0,
0,
1,
1,
8,
84,
13,
11,
1148,
33709,
83926,
31238,
12034
};

TGraph *g = new TGraph(21,x,y);
g->Draw("ac*");

}
   const char *people[nx] = {"Jean","Pierre","Marie","Odile",
      "Sebastien","Fons","Rene","Nicolas","Xavier","Greg",
      "Bjarne","Anton","Otto","Eddy","Peter","Pasha",
      "Philippe","Suzanne","Jeff","Valery"}

*/
