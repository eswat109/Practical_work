#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;

const char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const vector<char> ERROR = {'M', 'a', 'l', 'f', 'o' , 'r', 'm', 'e', 'd', ' ', 'i', 'n', 'p', 'u', 't' };
const vector<char> EMPTY = {'E', 'm', 'p', 't', 'y', ' ', 's', 't', 'r', 'i', 'n', 'g' };


char Char(int C){
    return base64[C];
}

int Int(char C){
    for (int i = 0; i < sizeof(base64)/sizeof(char); i++)
        if ( C == base64[i] )
            return i;
}

vector<char> encode_w(vector<char> a){
    vector<char> b;
    if (a.size() < 1 || a.size() > 3) return b;
    int tmp1 = 0;
    int tmp2;
    for (int i = 0; i < a.size(); i++){
        tmp1 = tmp1 << 8;
        tmp1 = tmp1 | int(a[i]);
    }
    tmp1 = tmp1 << 2*(3 - a.size());
    for (int i = a.size(); i >= 0; i--){
        tmp2 = (tmp1 >> 6*i) & 0x3f;
        b.push_back(Char(tmp2));
    }
    for (int i = 0; i < 3 - a.size(); i++){
        b.push_back('=');
    }
    return b;
}

vector<char> encode(vector<char> s){
    vector<char> tmp1, tmp2, ans;
    if ( s.size() == 0 ) return EMPTY;
    for (int i = 0; i < s.size(); i++){
        tmp1.push_back(s[i]);
        if (tmp1.size()%3 == 0){
            tmp2 = encode_w(tmp1);
            ans.insert(ans.end(), tmp2.begin(), tmp2.end());
            tmp1.clear();
        }
    }
    tmp2 = encode_w(tmp1);
    ans.insert(ans.end(), tmp2.begin(), tmp2.end());
    return ans;
}

vector<char> decode_w(vector<char> a){
    vector<char> b;
    while(a.back() == '=')
        a.pop_back();
    int tmp1 = 0;
    int tmp2;
    for (int i = 0; i < a.size(); i++){
        tmp1 = tmp1 << 6;
        tmp1 = tmp1 | Int(a[i]);
    }
    tmp1 = tmp1 >> 2*(4 - a.size());
    for (int i = a.size()-2; i >= 0; i--){
        tmp2 = (tmp1 >> 8*i) & 0xff;
        if ( tmp2 > 127 ) return ERROR;
        b.push_back(char(tmp2));
    }
    return b;
}

vector<char> decode(vector<char> s){
    if (s.size()%4 != 0){
        return ERROR;
    }
    if ( s.size() == 0 ) return EMPTY;
    vector<char> tmp1, tmp2, ans;
    for (int i = 0; i < s.size(); i++){
        tmp1.push_back(s[i]);
        if (tmp1.size()%4 == 0){
            tmp2 = decode_w(tmp1);
            if (tmp2 == ERROR) return ERROR;
            ans.insert(ans.end(), tmp2.begin(), tmp2.end());
            tmp1.clear();
        }
    }
    /*if ( !tmp1.empty() ){
        tmp2 = decode_w(tmp1);
        if (tmp2 == ERROR) return ERROR;
        ans.insert(ans.end(), tmp2.begin(), tmp2.end());
    }*/
    //if ( !tmp1.empty() ) return ERROR;
    return ans;
}

void test_encode_w(){
    {
        vector<char> inpt = {'1', '2', '3' };
        vector<char> encode_inpt = encode_w(inpt);
        vector<char> expected = { 'M', 'T', 'I', 'z' };
        assert(encode_inpt == expected);
    }
    {
        vector<char> inpt = {'1', '2' };
        vector<char> encode_inpt = encode_w(inpt);
        vector<char> expected = { 'M', 'T', 'I', '=' };
        assert(encode_inpt == expected);
    }
    {
        vector<char> inpt = {'1' };
        vector<char> encode_inpt = encode_w(inpt);
        vector<char> expected = { 'M', 'Q', '=', '=' };
        assert(encode_inpt == expected);
    }
    cout << "Test done successful" << endl;
}

void test_decode_w(){
    {
        vector<char> inpt = { 'M', 'T', 'I', 'z' };
        vector<char> expected = {'1', '2', '3' };
        vector<char> encode_inpt = decode_w(inpt);
        assert(encode_inpt == expected);
    }
    {
        vector<char> inpt = { 'M', 'T', 'I', '=' };
        vector<char> expected = {'1', '2' };
        vector<char> encode_inpt = decode_w(inpt);
        assert(encode_inpt == expected);
    }
    {
        vector<char> inpt = { 'M', 'Q', '=', '=' };
        vector<char> expected = {'1' };
        vector<char> encode_inpt = decode_w(inpt);
        assert(encode_inpt == expected);
    }
    cout << "Test done successful" << endl;
}

void test_encode(){
    {
        vector<char> inpt = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
        vector<char> expected = {'S', 'G', 'V', 's', 'b', 'G', '8', 'g', 'd', '2', '9', 'y', 'b', 'G', 'Q', 'h' };
        vector<char> encode_inpt = encode(inpt);
        assert(encode_inpt == expected);
    }
    cout << "Test Encode done successful" << endl;
}

void test_decode(){
    {
        vector<char> inpt = {'S', 'G', 'V', 's', 'b', 'G', '8', 'g', 'd', '2', '9', 'y', 'b', 'G', 'Q', 'h' };
        vector<char> expected = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == expected);
    }
    {
        vector<char> inpt = {'S', 'G', 'l', 'y', 't' };
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == ERROR);
    }
    {
        vector<char> inpt = {'S', 'G', 'l', 'y', 't', 'A' };
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == ERROR);
    }
    {
        vector<char> inpt = {'S', 'G', 'l', 'y', 't', 'A', 'A' };
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == ERROR);
    }
    {
        vector<char> inpt = {'a', 'a', 'a', 'a'};
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == ERROR);
    }
    {
        vector<char> inpt = {};
        vector<char> decode_inpt = decode(inpt);
        assert(decode_inpt == EMPTY);
    }
    cout << "Test Decode done successful" << endl;
}

void test_endecode(){
    {
        vector<char> inpt = {'S', 'G', 'V', 's', 'b', 'G', '8', 'g', 'd', '2', '9', 'y', 'b', 'G', 'Q', 'h' };
        vector<char> expected = {'S', 'G', 'V', 's', 'b', 'G', '8', 'g', 'd', '2', '9', 'y', 'b', 'G', 'Q', 'h' };
        vector<char> endecode_inpt = encode(decode(inpt));
        assert(endecode_inpt == expected);
    }
    {
        vector<char> inpt = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
        vector<char> expected = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!' };
        vector<char> endecode_inpt = decode(encode(inpt));
        assert(endecode_inpt == expected);
    }
    cout << "Test EnDecode done successful" << endl;
}

void test_all(){
    test_encode_w();
    test_decode_w();
    test_encode();
    test_decode();
    test_endecode();
}

vector<char> readf(ifstream &fin){
    vector<char> tmp;
    char c;
    if (fin.eof()) return tmp;
    while(!fin.eof()){
        fin.get(c);
        //cout << c << " ";
        tmp.push_back(c);
    }
    tmp.pop_back();
    return tmp;
}

int main(){
    test_all();

    ifstream fin("input.txt");
    ofstream fout("output.txt");
    vector<char> a, b, c;
    a = readf(fin);
    b = encode(a);
    for ( int i = 0; i < b.size(); i++ )
        fout <<b[i];
    fout << endl;
    c = decode(b);
    for ( int i = 0; i < c.size(); i++ )
        fout <<c[i];
    fout << endl;
    return 0;
}
