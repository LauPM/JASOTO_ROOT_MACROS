void doExtract(string s,int number){
// TFile *_file0 = TFile::Open(filename);
// gROOT->ProcessLine(".L extract.C+");
// extract a(ntp2);
// a.Loop(0,0,0,0);
// cout<<filename<<number<<endl;
  #include <iostream>
  #include <fstream> 
  using namespace std;
  ofstream myfile;
  myfile.open ("example.txt");
  myfile << "Writing this to a file.\n"<<s<<number;
  myfile.close();
}