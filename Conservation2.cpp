#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int Conservation2() {
TCanvas *c1 = new TCanvas("c1", "", 800,600);
TCanvas *c2 = new TCanvas("c2", "", 800,600);
TCanvas *c3 = new TCanvas("c3", "", 800,600);
TCanvas *c4 = new TCanvas("c4", "", 800,600);
TCanvas *c5 = new TCanvas("c5", "", 800,600);
TCanvas *c6 = new TCanvas("c6", "", 800,600);

TH1D* h1 = new TH1D("h1", "Initial X-Direction Momentum Distribution (second file, all events)", 500, -2.5, 2.5);
h1->GetXaxis()->SetTitle("Momentum [GeV/c]");
h1->GetYaxis()->SetTitle("Number of Particles");

TH1D* h2 = new TH1D("h2", "Initial Y-Direction Momentum Distribution (second file, all events)", 500, -2.5, 2.5);
h2->GetXaxis()->SetTitle("Momentum [GeV/c]");
h2->GetYaxis()->SetTitle("Number of Particles");

TH1D* h3 = new TH1D("h3", "Initial Z-Direction Momentum Distribution (second file, all events)", 500, -15, 15);
h3->GetXaxis()->SetTitle("Momentum [GeV/c]");
h3->GetYaxis()->SetTitle("Number of Particles");

TH1D* h4 = new TH1D("h4", "Freeze-Out X-Direction Momentum Distribution (second file, all events)", 500, -2.5, 2.5);
h4->GetXaxis()->SetTitle("Momentum [GeV/c]");
h4->GetYaxis()->SetTitle("Number of Particles");

TH1D* h5 = new TH1D("h5", "Freeze-Out Y-Direction Momentum Distribution (second file, all events)", 500, -2.5, 2.5);
h5->GetXaxis()->SetTitle("Momentum [GeV/c]");
h5->GetYaxis()->SetTitle("Number of Particles");

TH1D* h6 = new TH1D("h6", "Freeze-Out Z-Direction Momentum Distribution (second file, all events)", 500, -15, 15);
h6->GetXaxis()->SetTitle("Momentum [GeV/c]");
h6->GetYaxis()->SetTitle("Number of Particles");

class momentum {
    public:
    string pstring; 
    long double pi; 
    long double sum = 0.0;    
    vector<long double> pvec; 
};

    ifstream f13file;
    f13file.open("F7FE55EFC32E77DAA45DA45DCD7091A8_3 (1).f13");
    
    momentum x;
    momentum y;
    momentum z; 

    momentum xf;
    momentum yf; 
    momentum zf; 

    vector<long double> imags; 
    vector<long double> fmags; 

    long double imag; 
    long double fmag; 

    long double imag_sum = 0;
    long double fmag_sum = 0;

    string line;

    int event_counter = 0; 

    while(getline(f13file, line)) {
        if (line.size() == 58) {
            event_counter = event_counter + 1;
        }
        if (line.size() > 172) {
            x.pstring = line.substr(81, 16);
            y.pstring = line.substr(97, 16);
            z.pstring = line.substr(113, 16);
            xf.pstring = line.substr(260, 16);
            yf.pstring = line.substr(276, 16);
            zf.pstring = line.substr(292, 16); 

            x.pi = stold(x.pstring); 
            y.pi = stold(y.pstring);
            z.pi = stold(z.pstring);
            xf.pi = stold(xf.pstring);
            yf.pi = stold(yf.pstring);
            zf.pi = stold(zf.pstring);

            x.pvec.push_back(x.pi); 
            y.pvec.push_back(y.pi); 
            z.pvec.push_back(z.pi); 
            xf.pvec.push_back(xf.pi); 
            yf.pvec.push_back(yf.pi); 
            zf.pvec.push_back(zf.pi); 

            x.sum = x.sum + x.pi;
            y.sum = y.sum + y.pi;
            z.sum = z.sum + z.pi;
            xf.sum = xf.sum + xf.pi;
            yf.sum = yf.sum + yf.pi;
            zf.sum = zf.sum + zf.pi;

            imag = sqrt((x.pi)*(x.pi) + (y.pi)*(y.pi) + (z.pi)*(z.pi));
            fmag = sqrt((xf.pi)*(xf.pi) + (yf.pi)*(yf.pi) + (zf.pi)*(zf.pi));

            imags.push_back(imag);
            fmags.push_back(fmag);

            imag_sum = imag_sum + imag; 
            fmag_sum = fmag_sum + fmag;
        }
    }
    
    
    for (int k = 0; k < x.pvec.size(); k++) {
        h1->Fill(x.pvec[k]);
        h2->Fill(y.pvec[k]);
        h3->Fill(z.pvec[k]);
        h4->Fill(xf.pvec[k]);
        h5->Fill(yf.pvec[k]);
        h6->Fill(zf.pvec[k]);
    }
c1->cd();
h1->Draw();
c2->cd();
h2->Draw();
c3->cd();
h3->Draw();
c4->cd();
h4->Draw();
c5->cd();
h5->Draw();
c6->cd();
h6->Draw();
//Number of events
cout<<"Number of events: ";
cout<<event_counter<<endl;
cout<<""<<endl;


//Checking momentum Conservation
cout<<"Sum of Initial X-components: ";
cout<<x.sum<<endl; 

cout<<"Sum of Initial Y-components: ";
cout<<y.sum<<endl; 

cout<<"Sum of Initial Z-components: ";
cout<<z.sum<<endl; 

cout<<"Sum of Freeze-out X-components: ";
cout<<xf.sum<<endl; 

cout<<"Sum of Freeze-out Y-components: ";
cout<<yf.sum<<endl; 

cout<<"Sum of Freeze-out Z-components: ";
cout<<zf.sum<<endl; 

if (x.sum == xf.sum) {
    cout<<"Momentum is conserved in the X-direction"<<endl;
}
else if (x.sum != xf.sum) {
    cout<<"Momentum is not conserved in the X-direction"<<endl;
}

if (y.sum == yf.sum) {
    cout<<"Momentum is conserved in the Y-direction"<<endl;
}
else if (y.sum != yf.sum) {
    cout<<"Momentum is not conserved in the Y-direction"<<endl;
}

if (z.sum == zf.sum) {
    cout<<"Momentum is conserved in the Z-direction"<<endl;
}
else if (z.sum != zf.sum) {
    cout<<"Momentum is not conserved in the Z-direction"<<endl;
}

if ((x.sum == xf.sum) && (y.sum == yf.sum) && (z.sum == zf.sum)) {
    cout<<"Momentum of all events is conserved"<<endl;
}
else {
    cout<<"Momentum of all events is not conserved"<<endl;
}


return 0; 
}