
#pragma once 

#include<vector>
#include<string>
#include<iostream>
#include<deque>
#include<iomanip>
#include<cstring>

class Bignumber final{
    private:
        const int POWER = 4;
        std::string str_num,str_float_num;
        std::deque<int>num;
        std::deque<int>float_num;
        bool mark = 0;
    public:
        Bignumber()=default;
        Bignumber(std::string& item){
            this->to_Bignumber(item);
        }
        Bignumber(double item){
            char *ch;
            std::string buf;
            //std::cout<<std::setprecision(15)<<item<<std::endl;
            sprintf(ch, "%.10lf",item);
            buf = ch; 
            this->to_Bignumber(buf);
        }

        ~Bignumber() = default;
        std::string to_string(){
            std::string ret;
            if(mark)ret.push_back('-');
            char ch[5];
            sprintf(ch,"%d",num.front());
            ret += ch;
            for(int i = num.size();i > 1;--i){
                sprintf(ch,"%04d",num[i-1]);
                ret += ch;
            }
            ret.push_back('.');
            sprintf(ch,"%d",float_num.front());
            ret+=ch;
            for(int i = 2;i <= float_num.size();++i){
                sprintf(ch,"%04d",float_num[i-1]);
                ret += ch;
            }
            return ret;
        }

        void to_Bignumber (std::string &st){
           if(st[0] == '-'){
               mark = 1;
               st.erase(0,1);
           }
           int dot_pos = st.find_first_of('.');
           
           str_num = st.substr(0,dot_pos);

            str_float_num = st.substr(dot_pos+1,st.length() - 1 - dot_pos);
            
           int len = (str_num.length() - 1) / POWER + 1;
           
           for(int i = 0;i < len; ++i){
                int x = 0;
                int end = str_num.length() - i * POWER;
                int start = 0 > (end - POWER)?0:(end - POWER);
                sscanf(str_num.substr(start,end-start).c_str(),"%d", &x);
                num.push_front(x);
           }
           len = (str_float_num.length() - 1) /POWER + 1;
           for(int i = 0;i < len; ++i){
                int x = 0;
                int end = str_float_num.length() - i * POWER;
                int start = 0 > (end - POWER)?0:(end - POWER);
                sscanf(str_float_num.substr(start,end-start).c_str(), "%d", &x);
                float_num.push_front(x);
           }
        }
        
        bool operator <(const Bignumber &other){//mark this 
            if(this == &other) return false;
            for(auto i = num.back(),j = other.num.back();i>=num.front();i-= 1,j-=1){

                if(!(num[i] >= other.num[j]))return true;
                if(!(num[i] == other.num[j]))return false;
            } 
             return false;
        }

        bool operator ==(const Bignumber &other){
            if(this == &other) return true;
            if(mark != other.mark)return false;
            if(!(num.size() == other.num.size())) return false;
            if(!(float_num.size() == other.float_num.size()))return false;
            for(int i = num.size() -1;i >= 0;++i){
               if(!(num[i] == other.num[i])) return false;
            }
            for(int i = float_num.size()-1;i>=0;++i){
                if(!(float_num[i] == other.float_num[i]))return false;
            } 
            return true;
        }

        bool operator <=(const Bignumber &other){
            if(this == &other) return true;
            return (*this < other || *this == other);
        }
        bool operator >(const Bignumber &other){
            if(this == &other) return false;
            return !(*this <= other);
        }
        bool operator >=(const Bignumber &other){
            if(this == &other) return true;
            return *this > other || *this==other;
        }
        bool operator !=(const Bignumber &other){
            if(this == &other) return false;
            return !(*this == other);
        }

        Bignumber &operator =(const Bignumber &other){
            if(this == &other) return *this;
            this->mark = other.mark;
            this->float_num = other.float_num;
            this->num = other.num;
            this->str_num = other.str_num;
            return *this;
        }

        Bignumber &operator =(const long double &item){
            char *ch;
            std::string buf;
            std::sprintf(ch, "%.10Lf",item);
            std::cout<<ch<<std::endl;
            buf = ch;
            return *this;
        }
};

    std::ostream& operator <<(std::ostream &fout, Bignumber &item){
           fout<<item.to_string();
            return fout;
        }

    std::istream& operator >>(std::istream &fin, Bignumber &item){
            std::string temp;
            fin>>temp;
            item.to_Bignumber(temp);
            return fin;
        } 