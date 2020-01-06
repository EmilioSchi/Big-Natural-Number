/*
A simple library to rappresent large natural
numbers with fixed number of bits.

Written by Emilio Schinina' (emilioschi@gmail.com), DEC 2019
File:	natural.h
*/

#ifndef _NATURAL_H_
#define _NATURAL_H_

#define _DEBUG_ false
#define _DEFAULT_SIZE_ 128

#define ASSERT(condition)\
 do { if(!(condition)){ std::cerr << "[ASSERT] "<< "\x1b[31m" << #condition <<  "\x1b[0m" << " @ " << __FILE__ << " (" << __LINE__ << ")" << std::endl; exit(1);}} while(0)

#define	SAFE_FREE(X)\
	do { if((X) != NULL) {free(X); X=NULL;} } while(0)

#define	uint		unsigned
#define	iterator	size_t

class natural {
private:
	bool* value;
	iterator size;

	std::string int2str(int);
	std::string sumnumberstring(std::string a, std::string);
public:
	// Constructor
	natural ();
	natural (const iterator);

	// Copy Constructor
	natural(const natural& source);

	// Destructor
	~natural();

	// Utility
	void print_bin ();
	void print_bin(std::string);
	void print_dec();
	iterator getsize();

	// Overloading
	struct proxy
	{
		natural *a;
		iterator idx;
		proxy(natural *a, iterator idx) : a(a), idx(idx) {}
		bool& operator= (const bool);
		operator bool() const;
	};

	proxy operator[] (const iterator);
	natural& operator= (const natural&);
	natural& operator=(unsigned long long);
	natural operator<< (const iterator);
	natural operator>> (const iterator);
	natural operator~ ();
	bool operator> (const natural&);
	bool operator< (const natural&);
	bool operator== (const natural&);
	bool operator!= (const natural&);
	bool operator>= (const natural&);
	bool operator<= (const natural&);
	natural operator| (const natural&);
	natural operator& (const natural&);
	natural operator+ (const natural&);
	natural operator- (const natural&);
	natural operator* (const natural&);
	natural operator/ (const natural&);
	natural operator% (const natural&);
	natural operator+= (const natural&);
	natural operator-= (const natural&);
	natural operator*= (const natural&);
	natural operator/= (const natural&);
	natural operator%= (const natural&);
	natural operator++ (int);
	natural operator-- (int);
};

#endif /* _NATURAL_H_ */
