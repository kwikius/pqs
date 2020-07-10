
PQS is a C++ library for modelling physical quantities. ( [PQS Wiki](https://github.com/kwikius/pqs/wiki) )

PQS has a long history. [I started working on PQS in maybe 2002/3](https://github.com/kwikius/pqs/wiki/History). 

In 2005/6, I [proposed PQS](https://github.com/kwikius/pqs/blob/master/doc/archive/pqs_3_1_1.zip) to be 
a [member of the Boost C++ libraries](https://lists.boost.org/Archives/boost/2006/05/105631.php)
where [there was a lot of discussion](https://lists.boost.org/Archives/boost/2006/06/index.php)
but [it was rejected](https://lists.boost.org/Archives/boost/2006/06/106557.php).

Anyway I resolved to resubmit PQS to Boost but, [after much strangeness there](https://bytes.com/topic/c/answers/805860-standing-giants-shoulders), 
I left boost behind and renamed the library to [quan](https://github.com/kwikius/quan-trunk).

I worked on quan for my own use for many years [and incorporated it into many if not most of my projects](https://github.com/kwikius/ArduIMU/blob/master/visualisation/complementary/complementary_algorithm.cpp).
During that time, the library acquired lots of features, unrelated to physical quantities.

Anyway recently, after contributing to [mpusz/units](https://github.com/mpusz/units) for a while, 
I decided to go back to the source and see how my old friend [PQS](https://github.com/kwikius/pqs/wiki) might look in C++23.

So far it is a fun journey :-)

Please See [the PQS Wiki](https://github.com/kwikius/pqs/wiki) for detailed documentation.

#### Acknowledgements
Thanks to [mpusz](https://github.com/mpusz/) and [mpusz/units](https://github.com/mpusz/units), 
which inspired me to get back to work on [PQS](https://github.com/kwikius/pqs/). There are many good parts to mpusz/units but as with any other library, some issues.
Rather than continue with submitting issues and pull requests on that library, I decided it easier to express these things in my own code.



