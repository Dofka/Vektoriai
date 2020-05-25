#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <algorithm>
#include <time.h>
#include<iterator>
#include<vector>

using namespace std;
template <class T> class Vec {
public: // interfeisas
 typedef T* iterator;
 typedef const T* const_iterator;
 typedef size_t size_type;
 typedef T value_type;
 // rule of three
 Vec() { create(); }
 explicit Vec(size_type n, const T& t = T{}) { create(n, t); }
 Vec(const Vec& v) { create(v.begin(), v.end()); }
 Vec& operator=(const Vec&);
 ~Vec() { uncreate(); }
 T& operator[](size_type i) { return data[i]; }
 const T& operator[](size_type i) const { return data[i]; }
 void push_back
(const T& t)
{
 if (avail == limit)
 grow();
 unchecked_append(t);
 }
 size_type size() const { return avail - data; }
 iterator begin() { return data; }
 const_iterator begin() const { return data; }
 iterator end() { return avail; }
 const_iterator end() const { return avail; }
 void resize(size_type t){
          avail = data+t;
      }
 // tęsinys ankstesnės skaidrės
private:
 iterator data; // kaip buvo anksčiau
 iterator avail; // pirmasis po paskutiniojo sukonstruoto Vector elementas
 iterator limit; // pirmasis po paskutiniojo Vector elementas
 // atminties išskyrimo valdymui
 allocator<T> alloc; // objektas atminties valdymui
 // išskirti atmintį (array) ir ją inicializuoti
 void create() ;
 void create(size_type, const T&);
 void create(const_iterator, const_iterator);
 // sunaikinti elementus array ir atlaisvinti atmintį
 void uncreate();
 // pagalbinės funkcijos push_back realizacijai
 void grow();
 void unchecked_append(const T&);
};

class zmones
{
    protected:
    string vardas_;
    string pavarde_;

    public:
        void virtual SetVardas(string s){vardas_ = s;}
        string virtual GetVardas()const{return vardas_;}
        void virtual SetPavarde(string a){pavarde_ = a;}
        string virtual GetPavarde()const{return pavarde_;}



};
class studentai : public zmones
{
    private:
        double galutinis_;
    public:
        void SetGalutinis(double d){galutinis_ = d;}
        double GetGalutinis()const{return galutinis_;}
        studentai& operator=(const studentai& mok);
};
string IntToStr(int n);
void rikiavimas(vector <studentai> mok, int failoSK); //rikiavimo funkcija
bool lyginimas( studentai& a,  studentai& b);
ofstream& operator << (ofstream& os, const studentai& mok);
template <class T>
void Vec<T>::create() {
 data = avail = limit = nullptr;
}
template <class T> void Vec<T>::create(size_type n, const T& val) {
 data = alloc.allocate(n); // grąžina ptr į array pirmą elementą
 limit = avail = data + n; // sustato rodykles į vietas
 uninitialized_fill(data, limit, val); // inicializuoja elementus val reikšme
}
template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
 data = alloc.allocate(j - i); // išskirti vietos j-i elementams
 limit = avail = uninitialized_copy(i, j, data); // nukopijuoja elementus iš intervalo
}
template <class T> void Vec<T>::uncreate() {
 if (data) {
 // sunaikinti (atbuline tvarka) sukonstruotus elementus
 iterator it = avail;
 while (it != data)
 alloc.destroy(--it);
 // atlaisvinti išskirtą atmintį. Turi būti data != nullptr
 alloc.deallocate(data, limit - data);
 }
 // reset'inam pointer'iuss - Vector'ius tuščias
 data = limit = avail = nullptr;
}
template <class T> void Vec<T>::grow() {
 // dvigubai daugiau vietos, nei buvo
 size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
 // išskirti naują vietą ir perkopijuoti egzistuojančius elementus
 iterator new_data = alloc.allocate(new_size);
 iterator new_avail = uninitialized_copy(data, avail, new_data);
 // atlaisvinti seną vietą
 uncreate();
 // reset'int rodykles į naujai išskirtą vietą
 data = new_data;
 avail = new_avail;
 limit = data + new_size;
}
// tariame, kad `avail` point'ina į išskirtą, bet neinicializuotą vietą
template <class T> void Vec<T>::unchecked_append(const T& val) {
 alloc.construct(avail++, val);
}

#endif // HEADER_H_INCLUDED
