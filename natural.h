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

typedef unsigned uint;

class natural {
private:
	bool* value;
	uint size;
public:
	// Constructor
	natural ();
	natural (uint);

	// Copy Constructor
	natural(const natural& source);

	// Destructor
	~natural();

	// Utility
	void print_bin ();
	void print_dec();
	uint getsize();

	// Overloading
	struct proxy
	{
		natural *a;
		uint idx;
		proxy(natural *a, uint idx) : a(a), idx(idx) {}
		bool& operator= (const bool);
		operator bool() const;
	};

	proxy operator[] (const uint);
	natural& operator= (const natural&);
	natural operator<< (const uint);
	natural operator>> (const uint);
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

};

#endif /* _NATURAL_H_ */
