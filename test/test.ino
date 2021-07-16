class Test {

public:
	template <typename T>
	T f1(int);

	template <typename T>
	T f2(int);
};


template <typename T>
T Test::f1(int v) {
	return v * 2.123;
}

template <typename T>
T Test::f2(int v) {
	return f1<int>(v);
}



Test test;

void setup(void) {

	Serial.begin(115200);

	Serial.println((float)test.f1<int>(123), HEX);

	Serial.println((float)test.f2<int>(123), HEX);
}


void loop(void) {
}
