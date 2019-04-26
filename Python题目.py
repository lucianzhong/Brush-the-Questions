
1. list tuple区别 
	List字面意思就是一个集合，在Python中List中的元素用中括号[]来表示，可以这样定义一个List: L = [12, 'China', 19.998]
	Tuple可以看做是一种“不变”的List，访问也是通过下标，用小括号（）表示：t = (3.14, 'China', 'Jason'),Tuple所谓的不可变指的是指向的位置不可变
	Dict是Python中非常重要的数据类型，就像它的字面意思一样，它是个活字典，其实就是Key-Value键值对，类似于HashMap，可以用花括号{},d = {'Adam': 95,'Lisa': 85,'Bart': 59, 'Paul': 75}
	set就像是把Dict中的key抽出来了一样，类似于一个List，但是内容又不能重复，通过调用set()方法创建：s = set(['A', 'B', 'C'])
	
	
2. 生成器和迭代器 
	迭代是Python最强大的功能之一，是访问集合元素的一种方式。迭代器是一个可以记住遍历的位置的对象。迭代器有两个基本的方法：iter() 和 next()
	生成器实际上是特殊的一种迭代器，即完全可以像使用迭代器一样使用生成器,使用yield而不是return语句返回结果。yield语句一次返回一个结果，在每个结果中间，挂起函数的状态，以便下次从它离开的地方继续执行
	 （1）使用生成器函数的返回值，返回一个生成器对象
	 （2）使用生成器表达式的返回值，返回一个生成器对象（生成器表达式在后面讲解）


3. python中类变量与实例变量的区别
	Python类中定义的变量分为类变量和实例变量（也叫成员变量、对象变量），
	类变量直接定义在类里面（不在函数里面），前面不会有一个self修饰；相反，实例变量大都定义在实例函数里面，通过“self.变量名”的方式进行定义	 

4.  Python的函数参数传递
	这里记住的是类型是属于对象的，而不是变量。而对象有两种,“可更改”（mutable）与“不可更改”（immutable）对象。
	在python中，strings, tuples, 和numbers是不可更改的对象，而 list, dict, set 等则是可以修改的对象。(这就是这个问题的重点)
	当一个引用传递给函数的时候,函数自动复制一份引用,这个函数里的引用和外边的引用没有半毛关系了.
	所以第一个例子里函数把引用指向了一个不可变对象,当函数返回的时候,外面的引用没半毛感觉.
	而第二个例子就不一样了,函数内的引用指向的是可变对象,对它的操作就和定位了指针地址一样,在内存里进行修改.

			a = 1
			def fun(a):
				print ("func_in",id(a) )  # func_in 41322472
				a = 2
				print ("re-point",id(a), id(2) )  # re-point 41322448 41322448
			print ("func_out",id(a), id(1) ) # func_out 41322472 41322472
			fun(a)
			print (a)  # 1


			a = []
			def fun(a):
				print ("func_in",id(a) ) # func_in 53629256
				a.append(1)
			print  ("func_out",id(a) )    # func_out 53629256
			fun(a)
			print (a)  # [1]


5. Python类的实例化有3个方法,即静态方法(staticmethod),类方法(classmethod)和 实例方法

		def foo(x):
			print("excuting foo(%s,%s)"%(self,x))

		class A(object):
			def foo(self,x):
				print("excuting foo(%s,%s)"%(self,x))

			@classmethod
			def class_foo(cls,x):
				print("excuting class_foo(%s,%s)"%(cls,x))

			@staticmethod
			def static_foo(x):
				print("excuting static_foo(%s)"%x)

		a=A()

		这里先理解下函数参数里面的self和cls.这个self和cls是对类或者实例的绑定,对于一般的函数来说我们可以这么调用foo(x),这个函数就是最常用的,
		它的工作跟任何东西(类,实例)无关.对于实例方法,我们知道在类里每次定义方法的时候都需要绑定这个实例,就是foo(self, x),为什么要这么做呢?
		因为实例方法的调用离不开实例,我们需要把实例自己传给函数,调用的时候是这样的a.foo(x)(其实是foo(a, x)).类方法一样,
		只不过它传递的是类而不是实例,A.class_foo(x).注意这里的self和cls可以替换别的参数,但是python的约定是这俩,还是不要改的好.

						实例方法		类方法					静态方法
		  a = A()		a.foo(x)	a.class_foo(x)		a.static_foo(x)
		   A	    	不可用	    A.class_foo(x)		A.static_foo(x)



6. 类变量和实例变量
		类变量：​是可在类的所有实例之间共享的值（也就是说，它们不是单独分配给每个实例的）。例如下例中，num_of_instance 就是类变量，用于跟踪存在着多少个Test 的实例。
		实例变量：实例化之后，每个实例单独拥有的变量。



7. Python自省,这个也是python彪悍的特性.
	自省就是面向对象的语言所写的程序在运行时,所能知道对象的类型.简单一句就是运行时能够获得对象的类型.比如type(),dir(),getattr(),hasattr(),isinstance().
		a=[1,2,3,4]
		b={'a':1,'b':2,'c':3}
		c=True
		print (type(a),type(b),type(c))
		print(isinstance(a,list))


8.  列表(list)推导式
	字典(dict)推导式
	集合(set)推导式

	#过滤掉长度小于3的字符串列表，并将剩下的转换成大写字母  #list
	names = ['Bob','Tom','alice','Jerry','Wendy','Smith']
	[name.upper() for name in names if len(name)>3] 
	print(names)

	# 快速更换key和value   #dict
	mcase = {'a': 10, 'b': 34}
	mcase_frequency = {v: k for k, v in mcase.items()}
	print(mcase_frequency)

	# 集合推导式跟列表推导式也是类似的。 唯一的区别在于它使用大括号{ }
	squared = {x**2 for x in [1, 1, 4]}
	print(squared)

	
9.  Python中单下划线和双下划线
	__foo__:一种约定,Python内部的名字,用来区别其他用户自定义的命名,以防冲突，就是例如__init__(),__del__(),__call__()这些特殊方法
	_foo:一种约定,用来指定变量私有.程序员用来指定私有变量的一种方式.不能用from module import * 导入，其他方面和公有一样访问；
	__foo:这个有真正的意义:解析器用_classname__foo来代替这个名字,以区别和其他类相同的命名,它无法直接像公有成员一样随便访问,通过对象名._类名__xxx这样的方式可以访问.

10. 迭代器和生成器
	这里有个关于生成器的创建问题面试官有考： 问： 将列表生成式中[]改成() 之后数据结构是否改变？ 答案：是，从列表变为生成器

	L=[x*x for x in range(10)]
	G=(x*x for x in range(10))
	print(L)
	print(G)
	print (next(G))
	print(list(G))

	print(  sum( [i for i in range(10000)])  )
	print ( sum( (i for i in range(10000)) ) )

	通过列表生成式，可以直接创建一个列表。但是，受到内存限制，列表容量肯定是有限的。而且，创建一个包含百万元素的列表，不仅是占用很大的内存空间，
	如：我们只需要访问前面的几个元素，后面大部分元素所占的空间都是浪费的。因此，没有必要创建完整的列表（节省大量内存空间）。
	在Python中，我们可以采用生成器：边循环，边计算的机制—>generator


11.  *args and **kwargs
	当你不确定你的函数里将要传递多少参数时你可以用*args.例如,它可以传递任意数量的参数
	**kwargs允许你使用没有事先定义的参数名
	
		当我们不知道向函数传递多少参数时，比如我们向传递一个列表或元组，我们就使用*args
		在我们不知道该传递多少关键字参数时，使用**kwargs来收集关键字参数

12. 装饰器的作用就是为已经存在的对象添加额外的功能
	装饰器是一个很著名的设计模式，经常被用于有切面需求的场景，较为经典的有插入日志、性能测试、事务处理等。装饰器是解决这类问题的绝佳设计，
	有了装饰器，我们就可以抽离出大量函数中与函数功能本身无关的雷同代码并继续重用。概括的讲，装饰器的作用就是为已经存在的对象添加额外的功能


12. 鸭子类型
	比如在python中，有很多file-like的东西，比如StringIO,GzipFile,socket。它们有很多相同的方法，我们把它们当作文件使用。
	又比如list.extend()方法中,我们并不关心它的参数是不是list,只要它是可迭代的,所以它的参数可以是list/tuple/dict/字符串/生成器等.
	鸭子类型在动态语言中经常使用，非常灵活，使得python不想java那样专门去弄一大堆的设计模式


13. 动态语言Python
	强类型语言(静态类型语言)是指需要进行变量/对象类型声明的语言，一般情况下需要编译执行。例如C/C++/Java/C
	弱类型语言(动态类型语言)是指不需要进行变量/对象类型声明的语言，一般情况下不需要编译(但也有编译型的)。例如PHP/ASP/Ruby/Python/Perl/ABAP/SQL/JavaScript/Unix Shell等等。

14. 函数重载主要是为了解决两个问题
		1.可变参数类型
		2.可变参数个数
	另外，一个基本的设计原则是，仅仅当两个函数除了参数类型和参数个数不同以外，其功能是完全相同的，此时才使用函数重载，
	如果两个函数的功能其实不同，那么不应当使用重载，而应当使用一个名字不同的函数。
	那么对于情况 1 ，函数功能相同，但是参数类型不同，python 如何处理？答案是根本不需要处理，因为 python 可以接受任何类型的参数，
	如果函数的功能相同，那么不同的参数类型在 python 中很可能是相同的代码，没有必要做成两个不同函数。
	那么对于情况 2 ，函数功能相同，但参数个数不同，python 如何处理？
	大家知道，答案就是缺省参数。对那些缺少的参数设定为缺省参数即可解决问题。因为你假设函数功能相同，那么那些缺少的参数终归是需要用的。
	好了，鉴于情况 1 跟 情况 2 都有了解决方案，python 自然就不需要函数重载了


15. Python函数式编程
	a=[1,2,3,4,5]
	b=filter(lambda x:x>3,a)
	print(list(b))

16.  copy(),deepcopy()的区别
	我们寻常意义的复制就是深复制，即将被复制对象完全再复制一遍作为独立的新个体单独存在。所以改变原有被复制对象不会对已经复制出来的新对象产生影响。 
	而浅复制并不会产生一个独立的对象单独存在，他只是将原有的数据块打上一个新标签，所以当其中一个标签被改变的时候，数据块就会发生变化，
	另一个标签也会随之改变。这就和我们寻常意义上的复制有所不同了。


17. python 类语法中有三种方法，实例方法，静态方法，类方法
	实例方法只能被实例对象调用，静态方法(由@staticmethod装饰的方法)、类方法(由@classmethod装饰的方法)，可以被类或类的实例对象调用。
		实例方法，第一个参数必须要默认传实例对象，一般习惯用self
		静态方法，参数没有要求。
		类方法，第一个参数必须要默认传类，一般习惯用cls

		class Foo(object):
			def instance_method(self):
				print("是类{}的实例方法，只能被实例对象调用".format(Foo))

			@staticmethod
			def static_method():
				print("是静态方法")

			@classmethod
			def class_method(cls):
				print("是类方法")

		foo=Foo()
		foo.instance_method()
		foo.static_method()
		foo.class_method()

		Foo.static_method()
		Foo.class_method()


		类方法用在模拟java定义多个构造函数的情况。由于python类中只能有一个初始化方法，不能按照不同的情况初始化类

		继承类中的区别:
		从下面代码可以看出，如果子类继承父类的方法，子类覆盖了父类的静态方法，
		子类的实例继承了父类的static_method静态方法，调用该方法，还是调用的父类的方法和类属性。
		子类的实例继承了父类的class_method类方法，调用该方法，调用的是子类的方法和子类的类属性。


18. 列表和元组之间的区别是？
	二者的主要区别是列表是可变的，而元组是不可变的。
	>>> mylist=[1,3,3]
	>>> mylist[1]=2
	>>> mytuple=(1,3,3)
	>>> mytuple[1]=2
	Traceback (most recent call last):
	File "<pyshell#97>", line 1, in <module>
	mytuple[1]=2
	TypeError: ‘tuple’ object does not support item assignment

19. 解释一下Python中的三元运算子	
	[on true] if [expression] else [on false]
	>>> a,b=2,3
	>>> min=a if a<b else b
	
	>>> print("Hi") if a<b else print("Bye")

	
20. 在Python中是如何管理内存的？
	Python有一个私有堆空间来保存所有的对象和数据结构。作为开发者，我们无法访问它，是解释器在管理它。但是有了核心API后，
	我们可以访问一些工具。Python内存管理器控制内存分配。
	另外，内置垃圾回收器会回收使用所有的未使用内存，所以使其适用于堆空间。

21. Python中的字典是什么？
	>>> roots={25:5,16:4,9:3,4:2,1:1}
	>>> type(roots)
	<class 'dict'>
	>>> roots[9]

	字典是不可变的，我们也能用一个推导式来创建它。
	>>> roots={x**2:x for x in range(5,0,-1)}
	>>> roots


22. 负索引和正索引不同，它是从右边开始检索

23.  Python中的pass,break,continue
	 在用Python写代码时，有时可能还没想好函数怎么写，只写了函数声明，但为了保证语法正确，必须输入一些东西，在这种情况下，
	 我们会使用pass语句。
	>>> def func(*args):
           pass 
	>>>

	break语句能让我们跳出循环
	continue语句能让我们跳到下个循环

24. 解释一下Python中的//，%和 ** 运算符
	//运算符执行地板除法（向下取整除），它会返回整除结果的整数部分
	>>> 7//2
	3

25. Python中有3个逻辑运算符：and，or，not
	解释一下Python中的成员运算符: 通过成员运算符‘in’和‘not in’，我们可以确认一个值是否是另一个值的成员
	解释一下Python中的身份运算符: 通过身份运算符‘is’和‘is not’，我们可以确认两个值是否相同


26.  在Python中如何使用多进制数字？
	二进制数字由0和1组成，我们使用 0b 或 0B 前缀表示二进制数
	>>> int(0b1010)
	使用bin()函数将一个数字转换为它的二进制形式
	>>> bin(0xf)
	‘0b1111’
	八进制数由数字 0-7 组成，用前缀 0o 或 0O 表示 8 进制数
	>>> oct(8)
	‘0o10’
	十六进数由数字 0-15 组成，用前缀 0x 或者 0X 表示 16 进制数
	>>> hex(16)
	‘0x10’ 
	>>> hex(15)
	‘0xf’

27.  怎样获取字典中所有键的列表？
	使用 keys() 获取字典中的所有键
	>>> mydict={'a':1,'b':2,'c':3,'e':5}
	>>> mydict.keys()
	dict_keys(['a', 'b', 'c', 'e'])

28. 为何不建议以下划线作为标识符的开头
	因为Python并没有私有变量的概念，所以约定速成以下划线为开头来声明一个变量为私有。
	所以如果你不想让变量私有，就不要使用下划线开头。


29.  Python优化性能
	import dis
	dis是个反汇编工具，将Python代码翻译成字节码指令
	print(dis.dis(swap1))
	

30. is 和 == 的区别
	is 表示的是对象标示符（object identity），而 == 表示的是相等（equality）
	is 的作用是用来检查对象的标示符是否一致，也就是比较两个对象在内存中的地址是否一样，而 == 是用来检查两个对象是否相等
	检查 a is b 的时候，其实相当于检查 id(a) == id(b)
	而检查 a == b 的时候，实际是调用了对象 a 的 __eq()__ 方法，a == b 相当于 a.__eq__(b)

	
31. join 和 + 比较
	当用操作符+连接字符串的时候，每执行一次+都会申请一块新的内存，然后复制上一个+操作的结果和本次操作的右操作符到这块内存空间，
	因此用+连接字符串的时候会涉及好几次内存申请和复制。而join在连接字符串的时候，会先计算需要多大的内存存放结果，
	然后一次性申请所需内存并将字符串复制过去，这是为什么join的性能优于+的原因。
	所以在连接字符串数组的时候，我们应考虑优先使用join。


32. 理解__new__和__init__的区别
	__init__函数并不是真正意义上的构造函数，__init__方法做的事情是在对象创建好之后初始化变量。真正创建实例的是__new__方法。
	__new__ 方法，可以决定返回那个对象，也就是创建对象之前，这个可以用于设计模式的单例、工厂模式。
	__init__ 是创建对象时调用的	
		
	在__new__方法中把类实例绑定到类变量_instance上，如果cls._instance为None表示该类还没有实例化过，实例化该类并返回。
	如果cls_instance不为None表示该类已实例化，直接返回cls_instance
	
	  单例模式：
		class Singleton(object):
		_instance=None
		def __new__(cls,*args,**kwargs):		
			if(cls._instance is None):
				cls._instance=object.__new__(cls,*args,**kwargs)
			return cls._instance

		s1=Singleton()
		s2=Singleton()

		print(s1)
		print(s2)

	
	工场模式：
		class Fruit(object):
			def __init__(self):		
				pass
			def print_color(self):
				pass


		class Apple(Fruit):
			def __init__(self):		
				pass
			def print_color(self):
				print("apple is red")


		class Orange(Fruit):
			def __init__(self):		
				pass
			def print_color(self):
				print("Orange is orange")


		apple=Apple()
		print(apple)


		class Factory_Fruit(object):
			fruits={"apple":Apple,"orange":Orange}

			def __new__(cls,name):
				if name in cls.fruits.keys():
					return cls.fruits[name]()
				else:
					return Fruit()

		fruit1=Factory_Fruit("apple")
		print(fruit1)


33. 到底什么是Python？你可以在回答中与其他技术进行对比?
	(1)Python是一种解释型语言。这就是说，与C语言和C的衍生语言不同，Python代码在运行之前不需要编译。其他解释型语言还包括PHP和Ruby。
	(2)Python是动态类型语言，指的是你在声明变量时，不需要说明变量的类型。你可以直接编写类似x=111和x="I'm a string"这样的代码，程序不会报错。
	(3)Python非常适合面向对象的编程（OOP），因为它支持通过组合（composition）与继承（inheritance）的方式定义类（class）。Python中没有访问说明符（access specifier，类似C++中的public和private），这么设计的依据是“大家都是成年人了”。
	(4)在Python语言中，函数是第一类对象（first-class objects）。这指的是它们可以被指定给变量，函数既能返回函数类型，也可以接受函数作为输入。类（class）也是第一类对象。
	(5)Python代码编写快，但是运行速度比编译语言通常要慢。好在Python允许加入基于C语言编写的扩展，因此我们能够优化代码，消除瓶颈，这点通常是可以实现的。numpy就是一个很好地例子，它的运行速度真的非常快，因为很多算术运算其实并不是通过Python实现的。
	(6)Python用途非常广泛——网络应用，自动化，科学建模，大数据应用，等等。它也常被用作“胶水语言”，帮助其他语言和组件改善运行状况。
	(7)Python让困难的事情变得容易，因此程序员可以专注于算法和数据结构的设计，而不用处理底层的细节。

34.对比一下dict中items与iteritems?
		D={'a':1,'b':2,'c':3,'d':4}
		print(D.items())

		print( D.iteritems() )

		for i in D.iteritems():
			print(i)

		for k,v in D.iteritems():
			print(v)

35. 如何知道一个Python对象的类型
		>>> type([]);type('');type(0);type({});type(0.0);type((1,))
		<type 'list'>
		<type 'str'>
		<type 'int'>
		<type 'dict'>
		<type 'float'>
		<type 'tuple'>
		
		tempList=[1,2,3,4];
		tempList.reverse()
		for x in tempList:
			print(x)

		tempTuple=(1,2,3,4)
		for x in tempTuple:
			print(x)

36. 用一个例子解释Python中的继承。
	继承允许一个类获得另一个类的所有成员(比如属性和方法)。继承提供代码可重用性，使创建和维护应用程序变得更容易。
	我们继承的类称为super-class，继承的类称为派生/子类
	以下是Python支持的不同类型的继承：
	（1）单一继承:派生类获取单个超类的成员。
	（2）Multi-level继承:从基类base1继承的派生类d1，d2继承自base2。
	（3）分层继承:从一个基类可以继承任意数量的子类
	（4）多重继承:派生类从多个基类继承。

37.字典根据键从小到大排序
	dic={"name":"zs","age":18,"city":"shenzhen","tel":12311221}
	list=sorted(dic.items(),key=lambda i:i[0],reverse=False)
	print(list)
	print ( dict(list) )


38. filter方法求出列表所有奇数并构造新列表，a = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
	a=[1,2,3,4,5,6,7,8,9];
	def fn(a):
		return a%2==1
	newList=filter(fn,a)
	newList=[i for i in newList]
	print(newList)
	
	
	a=[1,2,3,4,5,6,7,8,9];
	res=[i for i in a if i%2==1]
	print(res)

	
39. extend可以将另一个集合中的元素逐一添加到列表中，区别于append整体添加

40. 自定义异常用于raise抛出异常
	def fn():
	try:
		for i in range(5):
			if i>2:
				raise Exception("数字大于2了")
	except Exception as ret:
		print(ret)

	fn()


41. [[1,2],[3,4],[5,6]]一行代码展开该列表，得出[1,2,3,4,5,6]
	a=[ [1,2], [3,4], [5,6] ]
	x=[ j for i in a for j in i]
	print(x)


42. try..except..else没有捕获到异常，执行else语句
	try..except..finally不管是否捕获到异常，都执行finally语句

43. 请将[i for i in range(3)]改成生成器
	a=(i for i in range(3))
	print ( type(a) )

	a=[i for i in range(3) ]
	print ( type(a) )

44. 排序
	(1)使用lambda函数对list排序foo = [-5,8,0,4,9,-4,-20,-2,8,2,-4]，输出结果为
		[0,2,4,8,8,9,-2,-4,-4,-5,-20]，正数从小到大，负数从大到小
		
		foo=[-5,8,0,4,9,-4,-20,-2,8,2,-4]
		a=sorted(foo,key=lambda x:(x<0,abs(x)))
		print(a)

	（2）列表嵌套元组，分别按字母和数字排序
		foo=[("zs",19),("ll",54),("wa",17),("df",23)]
		a=sorted(foo,key=lambda x:x[1],reverse=True)
		print(a)
		a=sorted(foo,key=lambda x:x[0])
		print(a)
		
	（3）根据字符串长度排序
		s=["ab","abc","a","abcd"];
		b=sorted(s,key=lambda x:len(x))
		print(b)
		print(s)
		s.sort(key=len)
		print(s)

45. 列表推导式、字典推导式、生成器
		import random
		td_list=[i for i in range(10)]
		print("列表推导式",td_list,type(td_list))

		ge_list=(i for i in range(10))
		print("列表 generator",ge_list,type(ge_list))

		dic={k:random.randint(4,9) for k in ["a","b","c","d"]}
		print("字典推导式",dic,type(dic))


46. 简述python引用计数机制
	python垃圾回收主要以引用计数为主，标记-清除和分代清除为辅的机制，其中标记-清除和分代回收主要是为了处理循环引用的难题。
	引用计数算法：
	当有1个变量保存了对象的引用时，此对象的引用计数就会加1
	当使用del删除变量指向的对象时，如果对象的引用计数不为1，比如3，那么此时只会让这个引用计数减1，即变为2，
	当再次调用del时，变为1，如果再调用1次del，此时会真的把对象进行删除

	class Animal(object):
	def __init__(self,name):
		print("__init__ ")
		self._name=name
	def __del__(self):
		print("__del__")
		print("delete ",self._name)

	cat=Animal("mao")
	cat1=cat
	cat2=cat
	cat3=Animal("xiaomao")
	print(id(cat),id(cat1),id(cat2),id(cat3))

	del cat
	del cat1
	del cat2
	del cat3




		
		
47. Python函数式编程：
	map()，reduce()，filter()	
	map函数会根据提供的函数对指定序列做映射
	filter函数会对指定序列执行过滤操作
	reduce函数，reduce函数会对参数序列中元素进行累积
	
	double_func=lambda s:s**2
	print (  map(double_func,[1,2,3,4])   )
	plus=lambda x,y :(x or 0)+(y or 0)
	print ( map(plus,[1,2,3],[4,5,6]) )
	print ( map(plus,[1,2,3],[1,2])  )
	
	plus=lambda x,y:x+y
	print ( reduce(plus,[1,2,3,4])  )
	
	
	mode2=lambda x:x%2
	print (  filter(mode2,[1,2,3,4,5,6,7])  )
			
		
48. 使用非绑定的类方法（用类名来引用的方法），并在参数列表中，引入待绑定的对象（self），从而达到调用父类的目的。
　　这样做的缺点是，当一个子类的父类发生变化时（如类B的父类由A变为C时），必须遍历整个类定义，
		把所有的通过非绑定的方法的类名全部替换过来，	
		
		
	class A:
	def __init__(self):
		print("enter A")
		print("leave A")
	class B(A):
		def __init__(self):
			print("enter B")
			A.__init__(self)
			print("leave B")
	b=B()

	尝试执行上面同样的代码，结果一致，但修改的代码只有一处，把代码的维护量降到最低，是一个不错的用法。因此在我们的开发过程中，
			super关键字被大量使用，而且一直表现良好。

　　在我们的印象中，对于super(B, self).__init__()是这样理解的：super(B, self)首先找到B的父类（就是类A），
	然后把类B的对象self转换为类A的对象（通过某种方式，一直没有考究是什么方式，惭愧），然后“被转换”的类A对象调用自己的__init__函数。
	考虑到super中只有指明子类的机制，因此，在多继承的类定义中，通常我们保留使用类似代码段1的方法。

	class A(object):
	 def __init__(self):
		print("enter A")
		print("leave A")

	class B(A):
		def __init__(self):
		print("enter B")
		super(B,self).__init__()
		print("leave B")

	b=B()


	支持多继承的传统的面向对象程序语言（如C++）是通过虚拟继承的方式去实现多继承中父类的构造函数被多次调用的问题，
	而Python则通过mro的方式去处理
		
		
49. 	
		装饰器本质上是一个 Python 函数或类，它可以让其他函数或类在不需要做任何代码修改的前提下增加额外功能，
		装饰器的返回值也是一个函数/类对象。它经常用于有切面需求的场景，
		比如：插入日志、性能测试、事务处理、缓存、权限校验等场景，装饰器是解决这类问题的绝佳设计。
		有了装饰器，我们就可以抽离出大量与函数功能本身无关的雷同代码到装饰器中并继续重用。
		概括的讲，装饰器的作用就是为已经存在的对象添加额外的功能。
		
		
50. 	现有字典 d= {'a':24,'g':52,'i':12,'k':33}请按value值进行排序?
		sorted(d.items(),key=lambda x:x[1])
		
		字典推导式
		d = {key:value for (key,value) in iterable}
		
		请反转字符串 "aStr"?
		print("aStr"[::-1])

		将字符串 "k:1 |k1:2|k2:3|k3:4"，处理成字典 {k:1,k1:2,...}
		str1 = "k:1|k1:2|k2:3|k3:4"
		def str2dict(str1):
			dict1 = {}
			for iterms in str1.split('|'):
				key,value = iterms.split(':')
				dict1[key] = value
			return dict1
			
			
		#字典推导式
		d = {k:int(v) for t in str1.split("|") for k, v in (t.split(":"), )}

		
		请按alist中元素的age由大到小排序
		alist = [{'name':'a','age':20},{'name':'b','age':30},{'name':'c','age':25}]
		def sort_by_age(list1):
			return sorted(alist,key=lambda x:x['age'],reverse=True)

			
		下面代码的输出结果将是什么？
		list = ['a','b','c','d','e']
		print(list[10:])
		代码将输出[],不会产生IndexError错误，就像所期望的那样，尝试用超出成员的个数的index来获取某个列表的成员。
		例如，尝试获取list[10]和之后的成员，会导致IndexError。然而，尝试获取列表的切片，开始的index超过了成员个数不会产生IndexError，
		而是仅仅返回一个空列表。这成为特别让人恶心的疑难杂症，因为运行的时候没有错误产生，导致Bug很难被追踪到。


		写一个列表生成式，产生一个公差为11的等差数列
		print([x*11 for x in range(10)])

		
		给定两个列表，怎么找出他们相同的元素和不同的元素？
		list1 = [1,2,3]
		list2 = [3,4,5]
		set1 = set(list1)
		set2 = set(list2)
		print(set1 & set2)
		print(set1 ^ set2)
		
		
		给定两个list A，B ,请用找出A，B中相同与不同的元素
		A,B 中相同元素： print(set(A)&set(B))
		A,B 中不同元素:  print(set(A)^set(B))


		请写出一段python代码实现删除list里面的重复元素？
		l1 = ['b','c','d','c','a','a']
		l2 = list(set(l1))
		print(l2)

		
51.		可变类型和不可变类型
		(1)可变类型有list,dict.不可变类型有string，number,tuple.
		(2)当进行修改操作时，可变类型传递的是内存中的地址，也就是说，直接修改内存中的值，并没有开辟新的内存。
		(3)不可变类型被改变时，并没有改变原内存地址中的值，而是开辟一块新的内存，将原地址中的值复制过去，对这块新开辟的内存中的值进行操作。
				
				
52. 单例
		#使用函数装饰器实现单例
		#使用类装饰器实现单例
		#使用 __new__ 关键字实现单例
		#使用 metaclass 实现单例


#使用函数装饰器实现单例
			def singleton(cls):
				_instance={}                #使用不可变的类地址作为键，其实例作为值，每次创造实例时，首先查看该类是否存在实例，存在的话直接返回该实例即可，否则新建一个实例并存放在字典中
				def inner():
					if cls not in _instance:
						_instance[cls]=cls()
					return _instance[cls]
				return inner

			@singleton
			class Cls(object):
				def __init__(self):
					pass

			cls1=Cls()
			cls2=Cls()
			print(id(cls1)==id(cls2))



			#使用 __new__ 关键字实现单例
			class Single(object):                                       #__builtin__.py中的object类，并将object类中的所有方法传承
				_instance=None                                          #一个类变量 _instance
				def __new__(cls,*args,**kwargs):                        #cls是当前正在实例化的类,多个位置参数和多个命名参数
					if cls._instance is None:                           #如果 _instance 为 None，则新建实例，否则直接返回 _instance 存放的实例。
						cls._instance=object.__new__(cls,*args,**kw)
					return cls._instance
				def __init__(self):                                     #self代表类的实例，而非类,代表当前对象的地址
					pass


			Single1=Single()
			Single2=Single()
			print( id(Single1)==id(Single2))

			
