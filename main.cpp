//#include <iostream>
#include <vector>
#include <fstream>
#include "audio.h"
#include <sstream>
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

    return  v_audio;
}

template <typename T,typename S>
vector<pair<T,T> > readFileStereo(string filename){

    ifstream file(filename,ios::in|ios::binary);

//determine the size of the file
//    cout<<"we here it started read"<<endl;
    file.seekg(0,file.end);;
    int fileSize=file.tellg();
    file.seekg(0,file.beg);
    double numberOfSamples;
    int size=sizeof(S);
    int channels =1;

    numberOfSamples= fileSize/(channels*(float)size);

    vector<T> v_audio;
    vector<pair<T,T> > v_stereo;
    v_audio.resize(numberOfSamples);

    file.read((char*)(&(v_audio[0])),(int)numberOfSamples);


    for(int i=0;i<v_audio.size()-1;i=i+2){
        v_stereo.push_back(make_pair(v_audio[i],v_audio[i+1]));
    }

    return  v_stereo;
}

template <typename T>
void writeFile(vector<T> &vec,string output){

    ofstream newFile(output, ios::out|ios::app);


    cout<<"file size in write "<<vec.size()<<endl;
    newFile.write( (char*)(&vec[0]), vec.size());
}

template <typename T>
void writeStereo(vector<pair<T,T>> &vec,string output){

    ofstream newFile(output, ios::out|ios::app);

    vector<T> v_audio;

    for(auto item:vec){
      v_audio.push_back(item.first);
      v_audio.push_back(item.second);
    }
    cout<<"file size in write "<<vec.size()<<endl;
    newFile.write( (char*)(&v_audio[0]), vec.size());
}

template <typename T,typename  S>
void add(string sound1,string sound2, string outputfileName){

        vector <S> vin = readFile<S>(sound1 );//frogs18sec_44100_signed_8bit_mono
        vector <S> vin2 = readFile<S>(sound2);//countdown40sec_44100_signed_8bit_mono
        if (vin.size() == vin2.size()) {
            audio < T, S > ad(vin);
            audio < T, S > ad2(vin2);
            audio < T, S > sum = ad + ad2;

            cout << "\n";
            // cout << "sum data is " << ad2.audio_data.size() << endl;
            writeFile(sum.audio_data, outputfileName);
        } else
            cout << "The two files are not the same length\n";
}

template <typename T,typename  S>
void addStereo(string sound1,string sound2, string outputfileName) {

        vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
        vector <S> vin2 = readFileStereo<T,S>(sound2 );//countdown40sec_44100_signed_8bit_mono
        if (vin.size() == vin2.size()) {
            audio < T, S > ad(vin);
            audio < T, S > ad2(vin2);
            audio < T, S > sum = ad + ad2;

            cout << "\n";
            // cout << "sum data is " << ad2.audio_data.size() << endl;
            writeStereo(sum.audio_data, outputfileName);
        } else
            cout << "The two files are not the same length, please use files with the same length\n";


}

// range add function
//function refused to be templated
void radd(string sound1,string sound2,int range1,int range2, string outputfileName,int bitCount){
if(bitCount ==8) {

    vector <int8_t> vin = readFile<int8_t>(sound1);
    vector <int8_t> vin2 = readFile<int8_t>(sound2);
    audio < int8_t, int8_t > ad(vin);
    audio < int8_t, int8_t > ad2(vin2);
    audio<int8_t, int8_t>::rangedAdd rAdd;//function object
    audio < int8_t, int8_t > range_sum = rAdd(ad, range1, range2, ad2, range1, range2);

    cout << "sum data is " << ad2.audio_data.size() << endl;
    writeFile(range_sum.audio_data, outputfileName);
} else{
    vector <int16_t> vin = readFile<int16_t>(sound1);
    vector <int16_t> vin2 = readFile<int16_t>(sound2);
    audio < int16_t, int16_t > ad(vin);
    audio < int16_t, int16_t > ad2(vin2);
    audio<int16_t, int16_t>::rangedAdd rAdd;//function object
    audio < int16_t, int16_t > range_sum = rAdd(ad, range1, range2, ad2, range1, range2);

    cout << "sum data is " << ad2.audio_data.size() << endl;
    writeFile(range_sum.audio_data, outputfileName);
}
}

//template <typename T,typename S>
void raddStereo(string sound1,string sound2,int range1,int range2, string outputfileName,int bitCount){

    if(bitCount ==8) {

        vector <int8_t> vin = readFile<int8_t>(sound1);
        vector <int8_t> vin2 = readFile<int8_t>(sound2);
        audio < int8_t, int8_t > ad(vin);
        audio < int8_t, int8_t > ad2(vin2);
        audio<int8_t, int8_t>::rangedAdd rAdd;//function object
        audio < int8_t, int8_t > range_sum = rAdd(ad, range1, range2, ad2, range1, range2);

        cout << "sum data is " << ad2.audio_data.size() << endl;
        writeFile(range_sum.audio_data, outputfileName);
    } else{
        vector <pair<int16_t,int16_t> > vin = readFileStereo<int16_t,pair<int16_t,int16_t> >(sound1);
        vector <pair<int16_t,int16_t> > vin2 = readFileStereo<int16_t,pair<int16_t,int16_t> >(sound2);
        audio < int16_t, pair<int16_t,int16_t>> ad(vin);
        audio < int16_t, pair<int16_t,int16_t>> ad2(vin2);
        audio<int16_t, pair<int16_t,int16_t>>::rangedAdd rAdd;//function object
        audio < int16_t,pair<int16_t,int16_t>> range_sum = rAdd(ad, range1, range2, ad2, range1, range2);

        //cout << "sum data is " << ad2.audio_data.size() << endl;
        writeStereo(range_sum.audio_data, outputfileName);
    }
}

template <typename T>
void cut(string sound1,string sound2,string outputfileName,int bitCount){

    vector <T> vin = readFile<T>(sound1);//frogs18sec_44100_signed_8bit_mono
    cout<<"about to write to the file"<<endl;
   vector <T> vin2 = readFile<T>(sound2);//countdown40sec_44100_signed_8bit_mono
    cout<<"about to write to the file1"<<endl;

    cout<<"about to write to the file2"<<endl;
 	audio<T, T> ad(vin);
 	audio<T, T> ad2(vin2);

 	audio<T,T> sum = ad|ad2;
//for(auto item:sum.audio_data){
    cout<<"size is: "<<sum.audio_data.size()<<" ";
//}
    writeFile(sum.audio_data,outputfileName);
}
template <typename T,typename S>
void cutStereo(string sound1,string sound2,string outputfileName,int bitCount){

    vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
    vector <S> vin2 = readFileStereo<T,S>(sound2 );//countdown40sec_44100_signed_8bit_mono
    cout<<"about to write to the file1"<<endl;

    cout<<"about to write to the file2"<<endl;
    audio<T, S> ad(vin);
    audio<T, S> ad2(vin2);

    audio<T,S> sum = ad|ad2;

    writeStereo(sum.audio_data, outputfileName);
}

template <typename T>
void volume(string sound1,string outputfileName,float r1,float r2){
    vector <T> vin = readFile<T>(sound1);
    audio<T, T> ad(vin);
    ad*pair<float,float>(r1,r2);
    int i=0;

    writeFile(ad.audio_data,outputfileName);
}


template <typename T,typename S>
void volume(string sound1,string outputfileName,float r1,float r2){
    vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
    audio<T, S> ad(vin);
    ad*pair<float,float>(r1,r2);

    writeStereo(ad.audio_data, outputfileName);
}

template <typename T>
void reverse(string sound1,string outputfileName){
    vector <T> vin = readFile<T>(sound1);
    audio<T, T> ad(vin);
    ad.reverse();

    writeFile(ad.audio_data,outputfileName);
}

template <typename T,typename S>
void reverse(string sound1,string outputfileName){
    vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
    audio<T, S> ad(vin);
    ad.reverse();

    writeStereo(ad.audio_data, outputfileName);
}

template <typename T>
void rms(string sound1,string outputfileName){
    vector <T> vin = readFile<T>(sound1);
    audio<T, T> ad(vin);
    ad.rms_cal();

    cout<<"The rms value is: "<<ad.rms<<endl;
}

template <typename T,typename S>
void rms(string sound1,string outputfileName){
    vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
    audio<T, S> ad(vin);
    ad.rms_cal();

    cout<<"The rms1(left) is: "<<ad.rms1<<endl;
    cout<<"The rms2(right) is: "<<ad.rms2<<endl;
}


template <typename T>
void norm(string sound1,string outputfileName, float range1, float range2){
    vector <T> vin = readFile<T>(sound1);
    audio<T, T> ad(vin);
    ad.normaliseAudio(range1);

    writeFile(ad.audio_data,outputfileName);
}

template <typename T,typename S>
void norm(string sound1,string outputfileName, float range1, float range2){
    vector <S> vin = readFileStereo<T,S>(sound1);//frogs18sec_44100_signed_8bit_mono
    audio<T, S> ad(vin);
    ad.normaliseAudio(range1,range2);

    writeStereo(ad.audio_data, outputfileName);
}



int main(int argc,char* argv[]) {
	//samp -r sampleRateInHz -b bitCount -c noChannels [-o outFileName ] [<ops>]soundFile1 [soundFile2]

 string outputfileName= argv[8];
	int sampleRate = stoi(argv[2]);
	int bitCount = stoi(argv[4]);
	int noChannels = stoi(argv[6]);

string ops = argv[9];

string sound1=argv[argc-1];
string sound2;//argv[argc-2] initialise in  the given option call



if(ops=="-add"){//adding the two audios
    sound2=argv[argc-2];
   if(noChannels==1) {
       if (bitCount == 8)
           add<int8_t, int8_t>(sound1, sound2, outputfileName);
       else
           add<int16_t, int16_t>(sound1, sound2, outputfileName);
       // cout<<"sound2 is "<<sound2<<endl;
       //cout<<"sound1 is "<<sound1<<endl;
   }
   if(noChannels==2){
       if (bitCount == 8)
           addStereo<int8_t, pair<int8_t,int8_t> >(sound1, sound2, outputfileName);
       else
           addStereo<int16_t, pair<int16_t,int16_t> >(sound1, sound2, outputfileName);
   }
}

if(ops=="-radd"){
int range1 = stoi(argv[argc-4]);
int range2 = stoi(argv[argc-3]);
sound2 = argv[argc-2];

    if(noChannels==1) {
        if (bitCount == 8)
        {
           radd(sound1,sound2,range1,range2,outputfileName,bitCount);
        }
        else{
            radd(sound1,sound2,range1,range2,outputfileName,bitCount);
        }


    }
    if(noChannels==2){
        if (bitCount == 8)
            raddStereo(sound1,sound2,range1,range2,outputfileName,bitCount);
        else
            raddStereo(sound1,sound2,range1,range2,outputfileName,bitCount);
    }



    }

    if(ops=="-cat") {
        sound2 = argv[argc-2];
        if(noChannels==1) {

            if (bitCount == 8)
            {
                cut<int8_t>(sound1,sound2,outputfileName,bitCount);
            }
            else{
                cut<int16_t>(sound1,sound2,outputfileName,bitCount);
            }


        }
        if(noChannels==2){
           if (bitCount == 8)
                cutStereo<int8_t,pair<int8_t,int8_t> >(sound1,sound2,outputfileName,bitCount);
            else
                cutStereo<int16_t,pair<int16_t,int16_t> >(sound1,sound2,outputfileName,bitCount);
        }

    }
    if(ops=="-v"){
        float range1 = stof(argv[argc-3]);
        float range2 = stof(argv[argc-2]);
        if(noChannels==1) {

            if (bitCount == 8)
            {

                volume<int8_t>(sound1,outputfileName,range1,range2);
            }
            else{
                volume<int16_t>(sound1,outputfileName,range1,range2);
            }


        }
        if(noChannels==2){
            if (bitCount == 8) {
                volume<int8_t,pair<int8_t,int8_t> >(sound1,outputfileName,range1,range2);
            }
            else{
                volume<int16_t,pair<int16_t,int16_t> >(sound1,outputfileName,range1,range2);
            }

        }

    }
    if(ops=="-rev") {
        if (noChannels == 1) {

            if (bitCount == 8) {
                reverse < int8_t > (sound1, outputfileName);
            } else {
                reverse < int16_t > (sound1, outputfileName);
            }

        }
        if (noChannels == 2) {
            if (bitCount == 8) {
                reverse < int8_t, pair<int8_t, int8_t> >(sound1, outputfileName);
            } else {
                reverse < int16_t, pair< int16_t, int16_t> >(sound1, outputfileName);
            }

        }
    }

    if(ops=="-rms"){
        if (noChannels == 1) {

            if (bitCount == 8) {
                rms <int8_t>(sound1, outputfileName);
            } else {
                rms <int16_t>(sound1, outputfileName);
            }

        }
        if (noChannels == 2) {
            if (bitCount == 8) {
                rms < int8_t, pair<int8_t, int8_t>>(sound1, outputfileName);
            } else {
                rms< int16_t, pair< int16_t, int16_t>>(sound1, outputfileName);
            }

        }
}
    if(ops=="-norm"){
        float range1 = stof(argv[argc-3]);
        float range2 = stof(argv[argc-2]);

        if (noChannels == 1) {

            if (bitCount == 8) {
                norm <int8_t>(sound1, outputfileName,range1,range2);
            } else {
                norm<int16_t>(sound1, outputfileName,range1,range2);
            }

        }
        if (noChannels == 2) {
            if (bitCount == 8) {
                norm<int8_t, pair<int8_t, int8_t>>(sound1, outputfileName,range1,range2);
            } else {
                norm<int16_t, pair<int16_t, int16_t>>(sound1, outputfileName,range1,range2);
            }

        }
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
 
