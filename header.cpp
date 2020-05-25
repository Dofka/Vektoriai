#include "header.h"

string IntToStr(int n)
{
    stringstream result;
    result << n;
    return result.str();
}
void rikiavimas(vector <studentai> mok, int failoSK) //rikiavimo funkcija
{

        for(int i=0;i<failoSK-1;i++)
        for(int j=i+1;j<failoSK;j++)
            if(mok[i].GetGalutinis()>mok[j].GetGalutinis())
            {
                swap(mok[i], mok[j]);
            }
}
bool lyginimas( studentai& a, studentai& b){
    return a.GetGalutinis() > b.GetGalutinis();
}
ofstream& operator << (ofstream& os, const studentai& mok)
{
                    os.width(15);
                    os<<mok.GetVardas()<<" ";
                    os.width(15);
                    os<<mok.GetPavarde()<<" ";
                    os.width(15);
                    os<<mok.GetGalutinis()<<endl;
                    return os;
}
studentai& studentai::operator=(const studentai& mok){
    if(this == &mok)
        return *this;
    this->vardas_ = mok.vardas_;
    this->pavarde_ = mok.pavarde_;
    this->galutinis_ = mok.galutinis_;
    return *this;
}

