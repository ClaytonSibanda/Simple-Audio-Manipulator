
#ifndef ASSIGNMENT5
#define ASSIGNMENT5
#include <algorithm>
#include <vector>
#include <cstdint>
#include <utility>
#include <numeric>
#include <math.h>
#include <iostream>

//now specialising the audio class 

template<typename T,typename S>
class audio{
 
  
  int sample;
  int channel;
  double sampling_rate;
  
 
 public:
 double rms;
 std::vector<S> audio_data;
  //constructor
  audio(int samp,int chn,double rate,std::vector<S> _data):sample(samp),channel(chn),sampling_rate(rate),audio_data(std::move(_data)){
    
  }
  
  audio(std::vector<S> _data):audio_data(std::move(_data)){
    
  }
  
  //copy constructor
  audio(const audio & ad):sample(ad.sample),channel(ad.channel),sampling_rate(ad.sampling_rate){
    std::cout<<"copy constructor\n";
    std::copy(ad.audio_data.begin(),ad.audio_data.end(),audio_data.begin());
    
  }
  //copy assignment operator
  
  audio & operator=(const audio & ad ){
    //avoid self copy
     std::cout<<"copy assignment\n";
    if(this!=&ad){
      // ad.this.clear()
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      //copy the vector now
      // std::cout<<"copy assignment ends0\n";
// std::copy(ad.audio_data.begin(),ad.audio_data.end(),audio_data.begin());
for(auto value: ad.audio_data){
  this->audio_data.push_back(value);
}
// std::cout<<"copy assignment ends\n";
    }
    return *this;
  }
  
  //move constructor
  audio(audio && ad){
   std::cout<<"move constructor\n";
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      audio_data=std::move(ad.audio_data);
    
  }
  
  //move assignment operator
  audio & operator=(audio && ad){
    //prevent self move
      std::cout<<"move assignment\n";
    if(this!=&ad){
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      audio_data=std::move(ad.audio_data);
      ad.sampling_rate=0;
      ad.channel=0;
      ad.sample=0;
    }
    return *this;
  }
  
  //concatenate the audio files
  audio<T,S>  operator|(audio<T,S> & rhs){
    //create a new audio file
      std::vector<S> new_v;
      audio<T,S> new_audio(new_v);
      std::cout<<"go here\n";
    if(sample==rhs.sample && channel==rhs.channel && sampling_rate==rhs.sampling_rate){
      new_audio=*this;
        std::cout<<"go here2\n";
      for(auto value:rhs.audio_data){
        
        new_audio.audio_data.push_back(value);
      }
    }
  
    
    return new_audio;
  }
  
  //volume factor for mono channel
  
  void operator*(std::pair<float,float> f){
    //create a new audio file
      std::vector<S> new_v;
      audio<T,S> new_audio(new_v);
      
      for(int i=0;i<this->audio_data.size();++i){
        this->audio_data[i]*=f.first;
      }
  }
  
  //for adding the two audio files
    audio<T,S>  operator+(audio<T,S> & rhs){
    //create a new audio file
      std::vector<S> new_v;
      audio<T,S> new_audio(new_v);
      std::cout<<"start adding\n";
    if(true){
    
        // std::cout<<"go here3\n";
      for(int i=0;i<rhs.audio_data.size();++i){
        if(this->audio_data[i]+rhs.audio_data[i]>1)
        new_audio.audio_data.push_back(this->audio_data[i]+rhs.audio_data[i]>127?127:this->audio_data[i]+rhs.audio_data[i]);
        else
        new_audio.audio_data.push_back(this->audio_data[i]+rhs.audio_data[i]<-128?-128:this->audio_data[i]+rhs.audio_data[i]);
      }
      std::cout<<" It addded\n";
    }
  
    
    return new_audio;
  }
  
  //cut operation for a mono channel sound
  void operator^(std::pair<int,int> f){
    //create a new audio file
    this->audio_data.erase(this->audio_data.begin()+f.first,this->audio_data.begin()+f.second+1);
  }
  
  void reverse(){
    std::reverse(this->audio_data.begin(),this->audio_data.end());
  }
  
//function object for rangedAdd
  class rangedAdd{
    public:
    audio<T,S> operator()(audio<T,S> & aud1,int aud1_first, int aud1_second,audio<T,S> & aud2,int aud2_first, int aud2_second){
      
      std::vector<S> new_v;
      new_v.resize(1+(aud1_second-aud1_first));
      audio<T,S> new_audio1(new_v);
      audio<T,S> new_audio2(new_v);
      
     std::copy(aud1.audio_data.begin()+aud1_first,aud1.audio_data.begin()+aud1_second+1,new_audio1.audio_data.begin());
     std::copy(aud2.audio_data.begin()+aud2_first,aud2.audio_data.begin()+aud2_second+1,new_audio2.audio_data.begin());
     
    audio<T,S> new_audio3(new_v);
    new_audio3=new_audio1+new_audio2;
    
 
    //std::cout<<"aud1 "<<(int)aud1<<" aud2 "<<(int)aud2<<"\n";
      return (new_audio1+new_audio2);
      
    }
  };
  
  //calculate the rms value of the audio clip
  void rms_cal(){
    int temp=std::accumulate(this->audio_data.begin(),this->audio_data.end(),0,[](int acc,int curr){
     return acc+(curr*curr); });
      
   this->rms=pow(temp/(float)this->audio_data.size(),0.5);

  }
  
// functor for normalising the sound clip
  template<typename W>
  class normalise{
    double rms;
     double desired;
  public:  
  
  normalise(double _rms,double desired):rms(_rms),desired(desired){ }
    double operator()(const W& ampl){
   
  
   return ampl*(desired/rms);
    }
  
    
  };
  
  void normaliseAudio(double desired){
    
    this->rms_cal();
    
    std::transform(this->audio_data.begin(),this->audio_data.end(),this->audio_data.begin(), normalise<S>(this->rms,desired));
    
    //clamp the data to its limits
    std::transform(this->audio_data.begin(),this->audio_data.end(),this->audio_data.begin(),[](S val)-> S{ if(val<-128)return -128;
      if(val>127) return 127;
      else
      return val;
    });
  }
  
  
};


template<typename T>
class audio<T, std::pair<T,T>>
{
  
  
  int sample;
  int channel;
  double sampling_rate;
  
 
 public:
double rms1;
 double rms2;
 std::vector<std::pair<T,T>> audio_data;
 
  //constructor
  audio(int samp,int chn,double rate,std::vector<std::pair<T,T>> _data):sample(samp),channel(chn),sampling_rate(rate),audio_data(std::move(_data)){
    
  }
  
  audio(std::vector<std::pair<T,T>> _data):audio_data(std::move(_data)){
    
  }
  
  //copy constructor
  audio(const audio & ad):sample(ad.sample),channel(ad.channel),sampling_rate(ad.sampling_rate){
    std::cout<<"copy constructor\n";
    std::copy(ad.audio_data.begin(),ad.audio_data.end(),audio_data.begin());
    
  }
  
  //copy assignment operator
  
  audio & operator=(const audio & ad ){
    //avoid self copy
     std::cout<<"copy assignment\n";
    if(this!=&ad){
      // ad.this.clear()
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      //copy the vector now
      // std::cout<<"copy assignment ends0\n";
// std::copy(ad.audio_data.begin(),ad.audio_data.end(),audio_data.begin());
for(auto value: ad.audio_data){
  this->audio_data.push_back(value);
}
// std::cout<<"copy assignment ends\n";
    }
    return *this;
  }
  
  //move constructor *************FINE
  audio(audio && ad){
   std::cout<<"move constructor\n";
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      audio_data=std::move(ad.audio_data);
    
  }
  
  //move assignment operator
  audio & operator=(audio && ad){
    //prevent self move
      std::cout<<"move assignment\n";
    if(this!=&ad){
      sampling_rate=ad.sampling_rate;
      channel=ad.channel;
      sample=ad.sample;
      audio_data=std::move(ad.audio_data);
      ad.sampling_rate=0;
      ad.channel=0;
      ad.sample=0;
    }
    return *this;
  } 
  
  
   //concatenate the audio files ***FINE
  audio<T,std::pair<T,T>>  operator|(audio<T,std::pair<T,T>> & rhs){
    //create a new audio file
      std::vector<std::pair<T,T>> new_v;
      audio<T,std::pair<T,T>> new_audio(new_v);
      std::cout<<"go here specialising\n";
      
    if(sample==rhs.sample && channel==rhs.channel && sampling_rate==rhs.sampling_rate){
      
      new_audio=*this;
        std::cout<<"go here2 specialising\n";
        
      for(auto value:rhs.audio_data){
        
        new_audio.audio_data.push_back(value);
      }
    }
       return new_audio;
  }
  
  
   //volume factor for stereo channel **FINE
  
  void operator*(std::pair<float,float> f){
    //create a new audio file
      std::vector<std::pair<T,T>> new_v;
      audio<T,std::pair<T,T>> new_audio(new_v);
      
      for(int i=0;i<this->audio_data.size();++i){
        this->audio_data[i].first*=f.first;
        this->audio_data[i].second*=f.second;
      }
  }
  
  
    //for adding the two audio stereo files *******FINE
    audio<T,std::pair<T,T>>  operator+(audio<T,std::pair<T,T>> & rhs){
    //create a new audio file
      std::vector<std::pair<T,T>> new_v;
      audio<T,std::pair<T,T>> new_audio(new_v);
      std::cout<<"start adding in stereo\n";
      T first;
      T second;
    if(true){
    
        // std::cout<<"go here3\n";
      for(int i=0;i<rhs.audio_data.size();++i){
        if((this->audio_data[i].first+rhs.audio_data[i].first)>1)
       first= this->audio_data[i].first+rhs.audio_data[i].first>127?127:this->audio_data[i].first+rhs.audio_data[i].first;
        else
       first= this->audio_data[i].first+rhs.audio_data[i].first<-128?-128:this->audio_data[i].first+rhs.audio_data[i].first;
        
        if((this->audio_data[i].second+rhs.audio_data[i].second)>1)
        second=this->audio_data[i].second+rhs.audio_data[i].second>127?127:this->audio_data[i].second+rhs.audio_data[i].second;
        else
     second= this->audio_data[i].second+rhs.audio_data[i].second<-128?-128:this->audio_data[i].second+rhs.audio_data[i].second;
     
        new_audio.audio_data.push_back(std::make_pair(first,second));
      }
      std::cout<<" It addded here stereo\n";
    }
  
    
    return new_audio;
  }
  
  
   //cut operation for a mono channel sound***FINE
  void operator^(std::pair<int,int> f){
    //create a new audio file
    this->audio_data.erase(this->audio_data.begin()+f.first,this->audio_data.begin()+f.second+1);
  }
  
    
  void reverse(){
    std::reverse(this->audio_data.begin(),this->audio_data.end());
  }
  
  
    
//function object for rangedAdd
  class rangedAdd{
    public:
    audio<T,std::pair<T,T>> operator()(audio<T,std::pair<T,T>> & aud1,int aud1_first, int aud1_second,audio<T,std::pair<T,T>> & aud2,int aud2_first, int aud2_second){
      
      std::vector<std::pair<T,T>> new_v;
      new_v.resize(1+(aud1_second-aud1_first));
      audio<T,std::pair<T,T>> new_audio1(new_v);
      audio<T,std::pair<T,T>> new_audio2(new_v);
      
     std::copy(aud1.audio_data.begin()+aud1_first,aud1.audio_data.begin()+aud1_second+1,new_audio1.audio_data.begin());
     std::copy(aud2.audio_data.begin()+aud2_first,aud2.audio_data.begin()+aud2_second+1,new_audio2.audio_data.begin());
     
    audio<T,std::pair<T,T>> new_audio3(new_v);
    new_audio3=new_audio1+new_audio2;
    
 
    //std::cout<<"aud1 "<<(int)aud1<<" aud2 "<<(int)aud2<<"\n";
      return (new_audio1+new_audio2);
      
    }
  };
  
  //calculate the rms value of the audio clip
  void rms_cal(){
    int temp1=std::accumulate(this->audio_data.begin(),this->audio_data.end(),0,[](int acc,std::pair<T,T> curr){
     return acc+(curr.first*curr.first); });
     
     int temp2=std::accumulate(this->audio_data.begin(),this->audio_data.end(),0,[](int acc,std::pair<T,T> curr){
     return acc+(curr.second*curr.second); }); 
     
   this->rms1=pow(temp1/(float)this->audio_data.size(),0.5);
   this->rms2=pow(temp2/(float)this->audio_data.size(),0.5);

  } 
  
  
  // functor for normalising the sound clip
  template<typename W>
  class normalise{
    double rms1;
    double rms2;
     double desired;
  public:  
  
  normalise(double _rms1,double _rms2,double desired):rms1(_rms1),rms2(_rms2),desired(desired){ }
  std::pair<T,T> operator()(const W& ampl){
   
  
   return std::make_pair((T)ampl.first*(desired/rms1),(T)ampl.second*(desired/rms2));
    }
  
    
  };
  
  void normaliseAudio(double desired){
    
    this->rms_cal();//calculate rms
    
    std::transform(this->audio_data.begin(),this->audio_data.end(),this->audio_data.begin(), normalise<std::pair<T,T>>(this->rms1,this->rms2,desired));
    
    int first;
    int second;
    //clamp the data to its limits
    std::transform(this->audio_data.begin(),this->audio_data.end(),this->audio_data.begin(),[&first,&second](std::pair<T,T> val)-> std::pair<T,T>{ 
      first=val.first;
      second=val.second;
      if(val.first<-128) val.first= -128;  if(val.second<-128) val.second= -128;
       if(val.first>127) val.first= 127;  if(val.second>127) val.second=127;
    
      return std::make_pair(first,second);
    });
  }
  

  
};



#endif 

 