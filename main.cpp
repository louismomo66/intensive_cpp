// #include <iostream>
// #include <list>

// using namespace std;

// class YoutubeChanel{
// public:
//     string Name;
//     string OwnerName;
//     int SubscribersCount;
//     list<string> PublishedVideos;

// };

// int main(){
// YoutubeChanel ytChannel;
// ytChannel.Name = "CodeBeauty";
// ytChannel.OwnerName = "Jane Doe";
// ytChannel.SubscribersCount = 1800;
// ytChannel.PublishedVideos = {"C++ Tutorial for Beginners", "Python Tutorial
// for Beginners", "Java Tutorial for Beginners"};

// cout << "Youtube Channel Name: " << ytChannel.Name << endl;
// cout << "Owner Name: " << ytChannel.OwnerName << endl;
// cout << "Subscribers Count: " << ytChannel.SubscribersCount << endl;
// cout << "Published Videos: " << endl;
// for(const string& video : ytChannel.PublishedVideos){
//     cout << "- " << video << endl;
// }

//     return 0;
// }
#include <iostream>

using namespace std;

class MusicalInstrument {
public:
  void MakeSound() { cout << "The instrunmet is playing a sound" << endl; }
};

class Piano : public MusicalInstrument {
public:
  void MakeSound() { cout << "The piano is playing a sound" << endl; }
};

class Guitar : public MusicalInstrument {
public:
  void MakeSound() { cout << "The guitar is playing a sound" << endl; }
};

int main() {
  MusicalInstrument *myInstrument = new Piano();
  MusicalInstrument *myInstrument2 = new Guitar();

  myInstrument->MakeSound();
  myInstrument2->MakeSound();
  return 0;
}