#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int totalday(int y, int m, int d);
int d_day(int fy, int fm, int fd, int sy, int sm, int sd);


int main(){
	int sy, sm, sd, fy, fm, fd, dates, n;
	char event[256]; //이벤트 이름
	int flag = 1; //while문 flag
	int option; //옵션

	struct tm *tm; //tm 구조체
	time_t t;
	tzset(); //시간대를 현재 지역 시간대로 설정

	time(&t); //시간 정보를 읽어서 변수 t에 저장
	tm = localtime(&t); //초 단위 시간을 tm 구조체 형태로 저장

	fy = (tm->tm_year)+1900; //현재 year
	fm = (tm->tm_mon)+1; //현재 month
	fd = (tm->tm_mday); //현재 day

	FILE *rfp;


	while(flag){
		printf("---------------옵션---------------\n"); //옵션 출력하기
		printf("1. 이벤트 목록의 디데이 확인하기\n");
		printf("2. 날짜 입력하고 디데이 확인하기\n");
		printf("3. 프로그램 종료\n");
		printf("옵션 1, 2, 3 중에 하나를 선택해주세요: ");
		scanf("%d", &option); //사용자로부터 옵션 입력받기
		printf("\n");

		switch(option){
			case 1: //옵션 1
				printf("-------------이벤트 목록의 디데이 확인하기-------------\n");
				if ((rfp = fopen("eventlist.dat", "r")) == NULL){
					                         //eventlist.dat 파일을 읽기모드로 염
					perror("fopen: eventlist.dat");
					exit(1);
				}
				while((n=fscanf(rfp, "%s %d %d %d", event, &sy, &sm, &sd)) != EOF){
					                             //이벤트 이름과 날짜를 읽어들임
					printf("이벤트: %s\n날짜: %d %d %d\n", event, sy, sm, sd);
					                             //이벤트 이름과 날짜를 출력
					d_day(fy, fm, fd, sy, sm, sd); //d_day 함수 호출
					printf("\n");
				}

				break;
			case 2: //옵션 2
				printf("-------------날짜 입력하고 디데이 확인하기-------------\n");
				printf("기념일 또는 이벤트의 날짜를 입력하세요(형식: yyyy mm dd)\n");
				scanf("%d %d %d", &sy, &sm, &sd); //사용자로부터 이벤트 날짜 입력받기
				d_day(fy, fm, fd, sy, sm, sd); //d_day 함수 호출
				break;
			case 3: //옵션 3
				flag = 0; //flag를 0으로 바꿔서 while문을 빠져나옴
				break;
		}
	}

	
	fclose(rfp); //파일 닫기

	return 0;
}

int totalday(int y, int m, int d){ //해당 날짜까지의 일수를 구하는 함수
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;
	int total = 0;

	total = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	//해당 년도의 전년도 까지의 일수 계산
	//4로 나누어 떨어지는 년도는 윤년. 
	//그 중 100으로 나누어 떨어지는 년도는 평년.
	//400으로 나누어 떨어지는 년도는 무조건 윤년.

        if (((y % 4)==0) && ((y % 100)!=0) || ((y % 400)==0)){ //해당 년도가 윤년이면 1일 증가
		months[1]+=1;
	}
        for (i = 0; i < m - 1; i++){ //1월부터 해당 월까지의 일수 계산
		total += months[i];
	}

        total += d; //해당 날짜까지의 총 일수

	return total;
}

int d_day(int fy, int fm, int fd, int sy, int sm, int sd){ //디데이를 구하고 출력하는 함수
	int dates;
	
	dates = totalday(fy, fm, fd) - totalday(sy, sm, sd); //디데이 계산

        if(dates < 0){ //입력한 날짜가 현재보다 나중일 경우
                printf("D%d\n", dates); //입력한 날짜까지 남은 일수 출력
        }
        else if(dates > 0){ //입력한 날짜가 현재보다 이전일 경우
                printf("D+%d\n", dates+1); //입력한 날짜부터 며칠째인지 출력(디데이 날짜를 1일로 포함)
        }
        else if(dates == 0){ //입력한 날짜와 현재 날짜와 같을 경우
                printf("D-day!!!\n"); //"D-day"라고 출력
        }

	return 0;
}
