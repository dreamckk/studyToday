#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>

using std::vector;
using std::string;

class StrBlob {
public:
	friend class StrBlobPtr;
	using size_type=vector<string>::size_type;
	StrBlobPtr begin();
	StrBlobPtr end();
	StrBlob() :data(std::make_shared<vector<string>>()) {}
	StrBlob(std::initializer_list<string> il) :data(std::make_shared<vector<string>>(il)) {}
	size_type size() const {
		return data->size();  
	}
	bool empty() const {          //make_shared()返回的是一个指针，指向vector<string> 
		return data->empty();     //所以data-> 是解引用指针，得到一个vector<string>
 	}                             //然后调用容器的成员函数push_back（），size(),empty()
	void push_back(const string& t) {
		data->push_back(t);
	}
	void pop_back() {                   //操作之前先检查索引是否在合法范围内
		check(0, "pop_back on empty StrBlob");
		return data->pop_back();
	}
	string& front() {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	string& back() {
		check(0, "back on empty StrBlon");
		return data->back();
	}
	//重载版本
	const string& front() const {
		check(0, "front on empty StrBlob");
		return data->front();
	}
	const string& back() const {
		check(0, "back on empty StrBlob");
		return data->back();
	}

private:
	std::shared_ptr<vector<string>> data;  //data是一个智能指针，指向底层vector
	void check(size_type i, const string& msg) const {
		if (i >= data->size()) //解引用指针并调用size（）函数，其实就是获得vector中元素的数目
			throw std::out_of_range(msg);
	}
};
class StrBlobPtr {
private:
	std::weak_ptr<vector<string>> wptr;
	std::size_t curr;
	std::shared_ptr<vector<string>> check(std::size_t, const string&) const;
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) :wptr(a.data), curr(sz) {} //默认情况下将curr初始化为第一个元素的下标
	string& deref() const;
	StrBlobPtr& incr();
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
}; 
std::shared_ptr<vector<string>> StrBlobPtr::check(std::size_t i, const string &msg) const {
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobStr");
	if (i >= ret->size())  //解引用指针并调用size（）函数，其实就是获得vector中元素的数目
		throw std::out_of_range(msg);  //出界
	return ret;  //若vector还存在，返回指向vector的智能指针
}
string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr]; //此处不能使用p->，因为下标需要输入成员名，否则会报错.
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr StrBlob::begin() {               /*为什么我把begin（）和end（）定义在StrBlob之内就会报错：使用未定义的类类型？*/
	return StrBlobPtr(*this); //
}
StrBlobPtr StrBlob::end() {
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}