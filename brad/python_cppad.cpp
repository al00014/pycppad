# include "setup.hpp"
# include "vector.hpp"

# define PY_ARRAY_UNIQUE_SYMBOL PyArrayHandle

# define PYTHON_CPPAD_OPERATOR_LIST    \
		.def(str(self))        \
                                       \
		.def(self + self)      \
		.def(self - self)      \
		.def(self * self)      \
		.def(self / self)      \
                                       \
		.def(self + double())  \
		.def(self - double())  \
		.def(self * double())  \
		.def(self / double())  \
                                       \
		.def(double() + self)  \
		.def(double() - self)  \
		.def(double() * self)  \
		.def(double() / self)

namespace python_cppad {
	// Replacement for the CppAD error handler
	void error_handler(
		bool known           ,
		int  line            ,
		const char *file     ,
		const char *exp      ,
		const char *msg      )
	{	if( ! known ) msg = 
			"Bug detected in python_cppad, Please report this.";

		PyErr_SetString(PyExc_ValueError, msg);
		boost::python::throw_error_already_set();
		// erorr handler must not return
	}
	// This ojbect lasts forever, so forever replacement of 
	// the default CppAD erorr handler 
	CppAD::ErrorHandler myhandler(error_handler);
	// -------------------------------------------------------------
	array vector2array(const double_vec& vec)
	{	int n = static_cast<int>( vec.size() );
		assert( n >= 0 );

		object obj(handle<>( PyArray_FromDims(1, &n, PyArray_DOUBLE) ));
		double *ptr = static_cast<double*> ( PyArray_DATA (
			reinterpret_cast<PyArrayObject*> ( obj.ptr() )
		));
		for(size_t i = 0; i < vec.size(); i++){
			ptr[i] = vec[i];
		}
		return  static_cast<array>( obj );
	}
	// -------------------------------------------------------------
	// Kludge: Pass level to Independent until we know how to determine if 
	// the elements are x_array are AD_double or AD_AD_double.
	void Independent(array& x_array, int level)
	{	PYTHON_CPPAD_ASSERT( 
			level == 1 || level == 2,
			"independent: level argument must be 1 or 2."
		);
		if( level == 1 )
		{	AD_double_vec x_vec(x_array);
			CppAD::Independent(x_vec);
		}
		else
		{	AD_AD_double_vec x_vec(x_array);
			CppAD::Independent(x_vec);
		}
	}
	// -------------------------------------------------------------
	// class ADFun_double
	//
	class ADFun_double {
	private:
		CppAD::ADFun<double> f_;
	public:
		// constructor
		ADFun_double(array& x_array, array& y_array)
		{	AD_double_vec x_vec(x_array);
			AD_double_vec y_vec(y_array);

			f_.Dependent(x_vec, y_vec);
		}
		// member function Forward
		array Forward(int p, array& xp)
		{	size_t     p_sz(p);
			double_vec xp_vec(xp);
			double_vec result = f_.Forward(p_sz, xp_vec);
			return vector2array(result);
		}
	};
	// -------------------------------------------------------------
	// class ADFun_AD_double
	//
	class ADFun_AD_double {
	private:
		CppAD::ADFun<AD_double> f_;
	public:
		// constructor
		ADFun_AD_double(array& x_array, array& y_array)
		{	AD_AD_double_vec x_vec(x_array);
			AD_AD_double_vec y_vec(y_array);

			f_.Dependent(x_vec, y_vec);
		}
		// Kludge: Version of Forward member function until we figure
		// out how to retrun an array with AD_double elements.
		// (This should look like forward for ADFun_double with
		// double replaced by AD_double.)
		void Forward(int p, array& xp, array& fp)
		{	size_t        p_sz(p);
			AD_double_vec xp_vec(xp);
			AD_double_vec result = f_.Forward(p_sz, xp_vec);

			// kludge to pass back result
			int* dims_ptr = PyArray_DIMS(fp.ptr());
			int ndim      = PyArray_NDIM(fp.ptr());
			size_t length = static_cast<size_t>( dims_ptr[0] );
			PYTHON_CPPAD_ASSERT( ndim == 1 , 
				"forward: third argument is not a vector."
			);
			PYTHON_CPPAD_ASSERT( length == f_.Range() , 
				"foward: third argument length not equal "
				"range dimension for function."
			);
			object *obj_ptr = static_cast<object*>( 
				PyArray_DATA(fp.ptr()) 
			);
			for(size_t i = 0; i < result.size(); i++)
			{	AD_double *ptr = 	
					& extract<AD_double&>(obj_ptr[i])(); 
				*ptr = result[i];
			}
			return;
		}
	};
	// -------------------------------------------------------------
}

BOOST_PYTHON_MODULE(python_cppad)
{
	// AD_double is used in python_cppad namespace
	typedef CppAD::AD<double>    AD_double;
	typedef CppAD::AD<AD_double> AD_AD_double;

	// here are the things we are using from boost::python
	using boost::python::numeric::array;
	using boost::python::class_;
	using boost::python::init;
	using boost::python::self;
	using boost::python::self_ns::str;

	using python_cppad::Independent;
	using python_cppad::ADFun_double;
	using python_cppad::ADFun_AD_double;

	// some kind of hack to get numpy working  ---------------------------
	import_array(); 
	array::set_module_and_type("numpy", "ndarray");
	// --------------------------------------------------------------------
	def("independent", &Independent);
	// --------------------------------------------------------------------
	class_<AD_double>("ad_double", init<double>())
		PYTHON_CPPAD_OPERATOR_LIST
	;

	class_<ADFun_double>("adfun_double", init< array& , array& >())
		.def("forward", &ADFun_double::Forward)
	;
	// --------------------------------------------------------------------
	class_<AD_AD_double>("ad_ad_double", init<AD_double>())
		PYTHON_CPPAD_OPERATOR_LIST
	;
	class_<ADFun_AD_double>("adfun_ad_double", init< array& , array& >())
		.def("forward", &ADFun_AD_double::Forward)
	;
}