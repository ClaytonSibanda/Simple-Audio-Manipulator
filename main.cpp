//#include <iostream>
#include <vector>
#include <fstream>
#include "audio.h"
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"

using namespace std;

template <typename T>
vector<T> readFile(string filename){

	ifstream file(filename,ios::in|ios::binary);

//determine the size of the file
//    cout<<"we here it started read"<<endl;
	file.seekg(0,file.end);;
	int fileSize=file.tellg();
	file.seekg(0,file.beg);
    double numberOfSamples;
	int size=sizeof(T);
	int channels =1;

	numberOfSamples= fileSize/(channels*(float)size);

	vector<T> v_audio;

	v_audio.resize(numberOfSamples);


	file.read((char*)(&(v_audio[0])),(int)numberOfSamples);
//	int i=0;
// for (auto item: v_audio){
//     cout<<(int)item<<endl;
//     if(i>50) break;
//     i++;
// }
    return  v_audio;
}

template <typename T>
void writeFile(vector<T> &vec,string output){

    ofstream newFile(output, ios::out|ios::app);

    cout<<"file size in write "<<vec.size()<<endl;
    newFile.write( (char*)(&vec[0]), vec.size());
}

template <typename T,typename  S>
void add(string sound1,string sound2, string outputfileName){
    vector<S> vin=readFile<S>(sound1+".raw");//frogs18sec_44100_signed_8bit_mono
    vector<S> vin2=readFile<S>(sound2+".raw");//countdown40sec_44100_signed_8bit_mono
if(vin.size()==vin2.size()) {
    audio < T, S > ad(vin);
    audio < T, S > ad2(vin2);
    audio < T, S > sum = ad + ad2;

    cout << "\n";
   // cout << "sum data is " << ad2.audio_data.size() << endl;
    writeFile(sum.audio_data, outputfileName);
}
else
    cout<<"The two files are not the same length\n";
}


int main(int argc,char* argv[]) {
	//samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>]soundFile1 [soundFile2]

 string outputfileName= argv[8];
	int sampleRate = stoi(argv[2]);
	int bitCount = stoi(argv[4]);
	int noChannels = stoi(argv[6]);

string ops = argv[9];

string sound1=argv[argc-1];
string sound2;//argv[argc-2]



if(ops=="-add"){//adding the two audios
    sound2=argv[argc-2];
    if(bitCount==8)
    add<int8_t,int8_t>(sound1,sound2,outputfileName);
    else
        add<int16_t,int16_t>(sound1,sound2,outputfileName);
   // cout<<"sound2 is "<<sound2<<endl;
    //cout<<"sound1 is "<<sound1<<endl;
}

if(ops=="-radd"){

        vector<int8_t> vin=readFile<int8_t>(sound1+".raw");
        vector<int8_t> vin2=readFile<int8_t>(sound1+".raw");

        audio<int8_t, int8_t> ad(vin);
        audio<int8_t, int8_t> ad2(vin2);
     audio<int8_t,int8_t>::rangedAdd rAdd;//function object
     audio<int8_t,int8_t> range_sum = rAdd(ad,0,3,ad2,0,3);

        cout<<"sum data is "<<ad2.audio_data.size()<<endl;
        writeFile(range_sum.audio_data,outputfileName);
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
 
