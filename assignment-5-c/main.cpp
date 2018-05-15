//#include <iostream>
#include <vector>
#include <fstream>
#include "audio.h"
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

using namespace std;

template <typename T>
vector<T> readFile(string filename){

	ifstream file(filename,ios::in|ios::binary) ;

//determine the size of the file
//    cout<<"we here it started read"<<endl;
	file.seekg(0,file.end);;
	int fileSize=file.tellg();
	file.seekg(0,file.beg);
	int numberOfSamples;
	int size=sizeof(T);
	int channels =1;
//    cout<<"we here it started read2"<<endl;
	numberOfSamples= fileSize/(channels*(float)size);

	vector<T> v_audio;
//	cout<<"Number of samples is "<<numberOfSamples<<"file size is "<<fileSize<<"\n";
	v_audio.reserve(numberOfSamples);

//    cout<<"we here it started read3"<<endl;
	file.read((char*)(&(v_audio[0])),(int)numberOfSamples);
	int i=0;
//    cout<<"we here it read"<<endl;
    return  v_audio;
}

template <typename T>
void writeFile(vector<T> vec,string output){
    int size = vec.size();
    ofstream OutFile;
    OutFile.open(output, ios::out | ios::binary);
    OutFile.write( (char*)&vec, size);
}

int main(int argc,char* argv[]) {
	//samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>]soundFile1 [soundFile2]

 string outputfileName= argv[8];
	int sampleRate = stoi(argv[2]);
	int bitCount = stoi(argv[4]);
	int noChannels = stoi(argv[6]);

string ops = argv[9];

string sound1=argv[10];
string sound2;
if(argc==12)
	sound2 = argv[11];
cout<<"sound2 is "<<sound2<<endl;
    cout<<"sound1 is "<<sound1<<endl;
if(ops=="-add"){
    cout<<"we here"<<endl;
    vector<int8_t> vin=readFile<int8_t>(sound1+".raw");
    vector<int8_t> vin2=readFile<int8_t>(sound2+".raw");
    cout<<"we here2"<<endl;
    audio<int8_t, int8_t> ad(vin);
    audio<int8_t, int8_t> ad2(vin2);
    audio<int8_t,int8_t> sum = ad|ad2;
    //write sum to a file

     writeFile(sum.audio_data,outputfileName);
}






/*************** FOR STEREO ****************/
	std::vector<pair<int8_t,int8_t>> v_audio3;
	std::vector<pair<int8_t,int8_t>> v_audio4;
		
	for(int i=1;i<6;i++){
	v_audio3.push_back(make_pair(i,i+1));
	v_audio4.push_back(make_pair(i+1,i+2));
	}
	
	audio<int8_t,pair<int8_t,int8_t>> aud1(v_audio3);
	audio<int8_t,pair<int8_t,int8_t>> aud2(v_audio4);
	
// 	for(auto item: aud1.audio_data)
// 	  cout<<"first is: "<<(int)item.first<<" second is: "<<(int)item.second<<endl;
	 
	//concatenate two audio files
// 	audio<int8_t,pair<int8_t,int8_t>> conct = aud1|aud2;
 //test  addition of audio files
 	// audio<int8_t,pair<int8_t,int8_t>> sum = aud1+aud2;
 
// audio<int8_t,pair<int8_t,int8_t>>::rangedAdd rAdd;//function object
// audio<int8_t,pair<int8_t,int8_t>> range_sum = rAdd(aud1,0,3,aud2,0,3);
 
 aud2.rms_cal();
// cout<<"rms1: "<<aud2.rms1<<" rms2: "<<aud2.rms2<<endl;
//  aud2.normaliseAudio( 29.0);//takes in the desired rms
//for(auto item: aud2.audio_data)
//	  cout<<"first is: "<<(int)item.first<<" second is: "<<(int)item.second<<endl;
	  


/*************** FOR MONO ****************/

	std::vector<int8_t> v_audio = {1, 1, 1, 1,1};
	std::vector<int8_t> v_audio2 = {2, 3, -11, 122, -128};
// 	audio<int8_t, int8_t> ad(v_audio);
// 	audio<int8_t, int8_t> ad2(v_audio2);

// 	audio<int8_t,int8_t> sum = ad|ad2;
	//  audio<int8_t,int8_t> sum1 = ad+ad2;
	// sum*pair<float,float>(1.2,3.0);
// 	ad ^ pair<int, int>(1, 3);
// ad.reverse();
// audio<int8_t,int8_t>::rangedAdd rAdd;//function object
// audio<int8_t,int8_t> range_sum = rAdd(ad,0,3,ad2,0,3);

// ad2.rms_cal();
// std::cout <<"The rms is: "<<ad2.rms<<endl;
// ad2.normaliseAudio( 12.0);//takes in the desired rms
// 	for (auto val : sum.audio_data) {
// 		cout << (int)val << endl;
// 	}
	


 }
 
