#include<iterator>
  #include<iostream>
  #include<vector>
  #include<cstdlib>
  using namespace std;
  //常用的一些函数算法
  namespace jj
  {
  	struct input_iterator_tag {};
  	struct output_iterator_tag {};
  	struct forward_iterator_tag :public input_iterator_tag {};
  	struct bidirectional_iterator_tag :public forward_iterator_tag {};
  	struct random_access_iterator_tag :public bidirectional_iterator_tag {};
  
  	template<class category,class t,class distance=ptrdiff_t,class pointer=t*,class reference=t&>
  	struct iterator
  	{
  		typedef category iterator_category;
  		typedef t       value_type;
  		typedef distance difference_type;
  		typedef pointer pointer;
  		typedef reference reference;
  	};
  	template<class iterator>
  	struct iterator_traits 
  	{
  		typedef typename iterator::iterator_category iterator_category;
  		typedef typename iterator::value_type   value_type;
  		typedef typename iterator::difference_type    difference_type;
  		typedef typename iterator::pointer    pointer;
  		typedef typename iterator::reference  reference;
  	};
  
  	template<class t>
  	struct iterator_traits<t*>
  	{
  		typedef random_access_iterator_tag    iterator_category;
  		typedef t   value_type;
  		typedef ptrdiff_t  difference_type;
  		typedef t* pointer;
  		typedef t& reference;
  	};
  	template<class t>
  	struct iterator_traits<const t*>
  	{
  		typedef random_access_iterator_tag    iterator_category;
  		typedef t   value_type;
  		typedef ptrdiff_t  difference_type;
  		typedef const t* pointer;
  		typedef const t& reference;
  	};
  	template<class iterator>
  	inline typename iterator_traits<iterator>::iterator_category
  		iterator_category(const iterator&)
  	{
  		typename iterator_traits<iterator>::iterator_category category;
  		return category();
  	}
  	template<class iterator>
  	inline typename iterator_traits<iterator>::value_type*
  		value_type(const iterator&)
  	{
  		return static_cast<typename iterator_traits<iterator>::value_type*>(0);
  	}
  
  	template<class iterator>
  	inline typename iterator_traits<iterator>::difference_type*
  		difference_type(const iterator&)
  	{
  		return static_cast<typename iterator_traits<iterator>::difference_type*>(0);
  	}
  	//以下是整组的distance函数
  
  	template<class inputiterator>
  	inline typename iterator_traits<inputiterator>::difference_type
  		_distance(inputiterator first, inputiterator last, input_iterator_tag)
  	{
  		typename iterator_traits<inputiterator>::difference_type n = 0;
  		while (first != last)
  		{
  			++first;
  			++n;
  		}
  		return n;
  	}
  
  	template<class randomaccessiterator>
  	inline typename iterator_traits<randomaccessiterator>::difference_type
  		_distance(randomaccessiterator first, randomaccessiterator last, random_access_iterator_tag)
  	{
  		return last - first;
  	}
  	template<class inputiterator>
  	inline typename iterator_traits<inputiterator>::difference_type
  		distance(inputiterator first, inputiterator last)
  	{
  		typedef typename 
  			iterator_traits<inputiterator>::iterator_category category;
  
  		return _distance(first, last, category());
  	}
  	//以下是advance函数
  	template<class inputiterator,class distance>
  	inline void _advance(inputiterator& i, distance n, input_iterator_tag)
  	{
  		while (n--)
  			++i;
  	}
  
  	template<class bidirectional,class distance>
  	inline void _advance(bidirectional& i, distance n, bidirectional_iterator_tag)
  	{
  		if (n >= 0)
  		{
  			while (n--)		++i;
  		}
  		else
  		{
  			while (n++)	--i;
  		}
  	}
  	template<class randomaccessiterator,class distance>
  	inline void _advance(randomaccessiterator& i, distance n, random_access_iterator_tag)
  	{
  		i += n;
  	}
  	template<class inputiterator,class distance>
  	inline void advance(inputiterator& i, distance n)
  	{
  		//typedef typename
  		//iterator_traits<inputiterator>::iterator_category	iterator_category
  		_advance(i, n, iterator_category(i));
  	}
  
  	template<class inputiterator, class t>
  	t accumulate(inputiterator first, inputiterator last, t init)
  	{
  		for (; first != last; ++first)
  		{
  			init = init + *first;
  		}
  		return init;
  	}
  	template<class inputiterator, class outputiterator, class t>
  	outputiterator _adjacent_difference(inputiterator first, inputiterator last, outputiterator result, t*)
  	{
  		t value = *first;
  		while (++first != last)
  		{
  			t tmp = *first;
  			*++result = tmp - value;
  			value = tmp;
  		}
  
  		return ++result;
  	}
  	template<class inputiterator,class outputiterator>
  	outputiterator adjacent_difference(inputiterator first, inputiterator last, outputiterator result)
  	{
  		if (first == last)	return result;
  		*result = *first;
  		
  		return _adjacent_difference(first, last, result, value_type(first));
  	}
  	template<class inputiterator1,class inputiterator2,class t>
  	t inner_product(inputiterator1 first1, inputiterator1 last1, inputiterator2 first2, t init)
  	{
  		for (; first1 != last1; ++first1, ++first2)
  			init = init + ((*first1) * (*first2));
  		return init;
  	}
  	template<class inputiterator,class outputiterator,class t>
  	outputiterator _partial_sum(inputiterator first, inputiterator last, outputiterator result, t*)
  	{
  		t value = *first;
  		while (++first != last)
  		{
  			value = value + *first;
  			*++result = value;
  		}
  
  		return ++result;
  	}
  	
  	template<class inputiterator,class outputiterator>
  	outputiterator partial_sum(inputiterator first,inputiterator last, outputiterator result)
  	{
  		if (first == last)
  			return result;
  		*result = *first;
  		return _partial_sum(first, last, result, value_type(first));
  	}
  	template<class t,class integer,class monoidoperation>
  	t power(t x, integer n, monoidoperation op)
  	{
  		if (n == 0)
  		{
  			//return identity_element(op);
  		}
  		else
  		{
  			while ((n & 1) == 0)
  			{
  				n >>= 1;
  				x = op(x, x);
  			}
  			t result = x;
  			n >>= 1;
  			while (n != 0)
  			{
  				x = op(x, x);
  				if ((n & 1) != 0)
  				{
  					result = op(result, x);
  				}
  				n >>= 1;
  			}
  
  			return result;
  		}
  	}
  	template<class forwarditerator,class t>
  	void iota(forwarditerator first, forwarditerator last, t value)
  	{
  		while (first != last)
  		{
  			*first++ = value++;
  		}
  	}
  
  }
  int main()
  {
  	int ia[] = { 1,2,3,4,5 };
  	vector<int>iv(ia, ia + 5);
  	ostream_iterator<int>oite(cout, " ");
  	cout << jj::accumulate(iv.begin(), iv.end(), 0) << endl;
  	jj::adjacent_difference(iv.begin(),iv.end(),oite);
  	return 0;
  }