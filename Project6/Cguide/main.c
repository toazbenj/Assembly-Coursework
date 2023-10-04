int result = 0x0;
int max(int x, int y) {
	if (x > y) {
		return x;
	}
	return y;
}
int main(void){
	int cnt = 0x01;
	
	
	while(cnt <0x10){
		cnt *= 2;
		result = max(cnt, 0x4 >> 1);
	}
	
	return 0;
}

