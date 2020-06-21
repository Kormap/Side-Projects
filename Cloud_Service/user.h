#pragma	once
#include					<unp.h>
#include					<string.h>
#define TRUE				(1)
#define FALSE				(0)
#define SUCCESS				(0)
#define ERROR				(-1)
#define DIR_PERMISIION		(00777)
#define USER_ID_LENGTH		(18)
#define PASSWORD_LENGTH		(14)
#define USER_TEXT			("user.txt")
#define BUF_SIZE			(32)
#define LSERVICE_LENGTH		(8)
#define clear()				if(system("clear") == ERROR) puts("clear Error..")
#define clear_buf()			while(getchar() != '\n')
#define pause()				getchar()
#define SUCCESS_SIG			("success")
#define FAIL_SIG			("sig")

typedef int				boolean;
typedef unsigned int 	INT;
typedef struct __login{
	char		user_id[USER_ID_LENGTH];
	char		password[PASSWORD_LENGTH];
}Login;

int		 	c_join(int sockfd);
int 		s_join(int sockfd);
boolean		s_login(int sockfd);
int			c_login(int sockfd, User *user);
int 		recv_login(int sockfd, Login *login); 
int 		send_login(int sockfd, Login *login);

/*		(client) User UI		*/

int c_user_ui(int sockfd, User *user) {
	int			n = 0;
	char		service[MAXLINE];
	boolean		first = TRUE;

	while(TRUE) {
		clear();
		if(!first)
			puts("Login Fail!!");
		puts("************************");
		puts("*  Select Service      *");
		puts("*                      *");
		puts("*  >>> ①  Login        *");
		puts("*                      *");
		puts("*  >>> ②  Join         *");
		puts("*                      *");
		puts("*  >>> ③  Exit         *");
		puts("*                      *");
		puts("************************");
		printf("\nINPUT : ");
	
		if( (n = scanf("%s", service) <= 0) || (n >= LSERVICE_LENGTH) )
			puts("Please Re-Enter");
	
		send(sockfd, service, MAXLINE, 0);	
		
		if( !strcmp(service, "1") || !strcmp(service, "login") ) {
			if(c_login(sockfd, user)) {
				puts("Login Success!!");
				return TRUE;
			}else {
				first = FALSE;
				puts("Login Fail!!");
			}
		}
		else if( !strcmp(service, "2") || !strcmp(service, "join") )
			c_join(sockfd);
		else if( !strcmp(service, "3") || !strcmp(service, "exit") )
			exit(SUCCESS);
		else{
			puts("Please Re-Enter");
			clear_buf();
			pause();
		}
	}
}

int s_user_ui(int sockfd) {
	char		service[MAXLINE];
	int			pid = (int)getpid();
	while(TRUE) {
		recv(sockfd, service, MAXLINE, 0);
		
		if( !strcmp(service, "1") || !strcmp(service, "login") ) {
			printf("process : %d : try Login\n", pid);
			if(s_login(sockfd)) 
				return TRUE;
		}
		else if( !strcmp(service, "2") || !strcmp(service, "join") ) {
			printf("process : %d : try Join\n", pid);
			s_join(sockfd);
		}
		else if( !strcmp(service, "3") || !strcmp(service, "exit") ){
			printf("process : %d : exit\n", pid);
			exit(SUCCESS);
		}else{
			puts("Error!!");
			exit(0);
		}
	}
}

/*		(client) Server에 login 구조체를 보내는 Func		*/

int send_login(int sockfd, Login *login){
	return send(sockfd, login, sizeof(struct __login), 0);
}


/*		(server) Client로부터 login 구조체를 받는 Func		*/

int recv_login(int sockfd, Login *login) {
	return recv(sockfd, login, sizeof(struct __login), 0);
}


/*		(server) 로그인 Func		*/

boolean s_login(int sockfd) {
	int				fd;
	char			buf[BUF_SIZE];
	char*			cmp_id;
	char*			cmp_pw;
	Login			login;

	recv_login(sockfd, &login);

	fd = open(USER_TEXT, O_RDONLY);
	if( fd == ERROR ) {
		perror("open");
		return ERROR;
	}

	while( Readline(fd, &buf, BUF_SIZE) > 0 ) {
		cmp_id = strtok(buf, "@");
		cmp_pw = strtok(NULL, "\n");

		if( !strcmp(login.user_id, cmp_id) && !strcmp(login.password, cmp_pw) ) {
			send(sockfd, SUCCESS_SIG, MAXLINE, 0);
			return TRUE;
		}
	}
	send(sockfd, FAIL_SIG, MAXLINE, 0);
	return FALSE;
}


/*		(client) 로그인 Func		*/

int c_login(int sockfd, User *user) {
	Login		login;
	int			n = 0;
	char		signal[MAXLINE];

	printf("ID		: ");
	while( (n = scanf("%s", login.user_id) <= 0 ) || (n >= USER_ID_LENGTH) )
		puts("Please Re-Enter");

	printf("PASSWORD	: ");
	while( (n = scanf("%s", login.password) <= 0 ) || (n >= PASSWORD_LENGTH) )
		puts("Please Re-Enter");

	strcpy(user->user_id, login.user_id);

	send_login(sockfd, &login);
	recv(sockfd, signal, MAXLINE, 0);

	if( !strcmp(signal, SUCCESS_SIG) )
		return TRUE;
	else if( !strcmp(signal, FAIL_SIG) )
		return FALSE;
	else{
		printf("signal : %s\n", signal);
		puts("Signal Error!!");
		return ERROR;
	}
}


/*		(client) 회원가입		*/

int c_join(int sockfd) {
	Login		login;
	int			n = 0;

	printf("ID		: ");
	while( (n = scanf("%s", login.user_id) <= 0 ) || (n >= USER_ID_LENGTH) )
		puts("Please Re-Enter");

	printf("PASSWORD	: ");
	while( (n = scanf("%s", login.password) <= 0) || (n >= PASSWORD_LENGTH) )
		puts("Please Re-Enter");

	send_login(sockfd, &login);

	return SUCCESS;
}

int s_join(int sockfd) {
	Login			login;
	int				fd;

	recv_login(sockfd, &login);

	fd = open(USER_TEXT, O_WRONLY | O_CREAT | O_APPEND, DIR_PERMISSION);

	if(fd == ERROR) {
		perror("open");
		return ERROR;
	}

	Write(fd, login.user_id, strlen(login.user_id));
	Write(fd, "@", 1);
	Write(fd, login.password, strlen(login.password));
	Write(fd, "\n", 1);

	return SUCCESS;
}

/*		End of Header		*/
/*		End of Header		*/
/*		End of Header		*/
