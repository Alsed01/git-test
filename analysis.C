void analysis()
{
    double dist[500], data[500], dist1[200], data1[200];

    int jMax=12;

	fstream file;
    string str1="elect_opt4_v500_denc";
    string str2a = "f-";
    string str2;
    string str3="_cut50_r100.csv";
    string str4="fit_";
    string str5=".png";
    string density = "0.9";
    string name;
    double aboba=2000;
    
    double lambda[jMax], field[jMax];
    
    int num=140;

 
    for (int i=0 ; i<500 ; i++ )
      {
          dist[i] = i+1*1.0;
          data[i] = 0;
      }
    for (int i=0 ; i<200 ; i++ )
      {
          dist1[i] = i+301;
          data1[i] = 0;
      }
    
    int n=0;
    double x_value, y_value, z_value, energy_value;
    string type, energy, z, x, y;
    
    for (int j=0 ; j<jMax ; j++ ) {
        stringstream ss;
        
        field[j] = num;
        ss<<num;
        ss>>str2;
        file.open(str1+density+str2a+str2+str3,ios::in);
        while(1)
        {
            file >> type >> energy >> energy_value >> z >> z_value >> x >>x_value >> y >> y_value;
            
            for (int i=0 ; i<500 ; i++ )
              {
                  if ((z_value<(i+1)*1.0) && (z_value>=0) ){
                      data[i]++;
                  }
              }
            if(file.eof()) break;
        }
       
for (int i=1 ; i<500 ; i++ )
  {
      data[i]=log(data[i]);
  }
        data[0]=data[1];
        
        for (int i=0 ; i<200 ; i++ )
        {
            data1[i] = data[i+300];
        }
        
TGraph *gr = new TGraph(500,dist,data);
TGraph *gr2 = new TGraph(200,dist1,data1);
gr->GetXaxis()->SetTitle("Z, m");
gr->GetYaxis()->SetTitle("Log(number of electrons)");
gr->SetMarkerStyle(kFullCircle);
gr->SetMarkerSize(0.2);

TCanvas *c1 = new TCanvas();
c1->SetTickx();
c1->SetTicky();
c1->SetGridx();
c1->SetGridy();


        
TF1 *fit = new TF1("fit", "pol1", 0, 500);
        
gr->GetYaxis()->SetLimits(0,50);
fit->GetYaxis()->SetLimits(0,50);
    
fit->SetParameter(0,10);
fit->SetParameter(1,0.01);
        
      
       
gr->SetTitle("");
gr->Draw("AP");
//gr->Fit("fit");
        

gr2->Draw("CP");
gr2->Fit("fit");
        

        
//TLegend *leg = new TLegend(0.4, 0.6, 0.65, 0.75);
//leg->SetBorderSize(0);
//leg->AddEntry(gr, "Data", "P");
//leg->AddEntry(fit, "Fit function", "l");
//leg->Draw();

        
lambda[j] = 1/(fit->GetParameter(1));

    
string filename = density+str4+str2+str5;
int length = filename.length();
char ch[length + 1];
strcpy(ch, filename.c_str());
c1->Print(ch);

    file.close();
        
    num  = num + 10;
    }
    
    //for (int i=0 ; i<500 ; i++ )
     // {
     //     gr->SetPoint(i,dist1[i],data1[i]);::
     // }
    cout << "Плотность" << density << ",  RREA: " ;
    for (int j=0 ; j<jMax ; j++ ) {
        cout <<  lambda[j] << "  ";
    }
    cout << endl;
    
    cout << "Плотность" << density << ",  field: " ;
    for (int j=0 ; j<jMax ; j++ ) {
        cout <<  field[j] << "  ";
    }
    cout << endl;
    
    TGraph *gr2 = new TGraph(jMax,field,lambda);
    gr2->GetXaxis()->SetTitle("field, keV/m");
    gr2->GetYaxis()->SetTitle("lambda, m");
    gr2->SetMarkerStyle(kFullCircle);
    gr2->SetMarkerSize(1);
    TCanvas *c1 = new TCanvas();
    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();
    
    
    TF1 *fit_RREA = new TF1("fit_RREA", "[0]/(x-[1])", 100, 300);
    
    gr2->SetTitle("");
    gr2->Draw("AP");
    gr2->Fit("fit_RREA");
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->AddEntry(gr2, "Measured Data", "p");
    leg->AddEntry(fit_RREA, "f(x)=p0/(x-p1)", "l");
    stringstream ss;
    ss<<fit_RREA->GetParameter(0);
    ss>>name;
    name="p0 = " + name;
    int length1 = name.length();
    char ch1[length1 + 1];
    strcpy(ch1, name.c_str());
    
    leg->AddEntry( "",ch1, "R");
    
    name="";
    stringstream ss1;
    ss1<<fit_RREA->GetParameter(1);
    ss1>>name;
    name="p1 = " + name;
    int length2 = name.length();
    char ch2[length2 + 1];
    strcpy(ch2, name.c_str());
    
    leg->AddEntry( "",ch2, "R");
   
    leg->Draw();
    
    string filename = density+"RREA.png";
    int length = filename.length();
    char ch[length + 1];
    strcpy(ch, filename.c_str());
    c1->Print(ch);
    cout << fit_RREA->GetParameter(1) << endl;
    
}

