/*
   *	2019-07-12 	~  2019-07-18 
   *	University	:	Kwangwoon University
   *	Department	:	Electronic Communication Engineering
   *	Student No	:	2014707073
   *	Name		:	Kim-Soo-Hwan
   *
   *	Project		:	Cloud-Service using Unix Network Programming
   *	Function	:	cloud_ser.c
   *	Role		:	Main of Server
*/
#define CRT_SECURES_NO_WARNINGS
#include			"unp.h"
#include			"server.h"
#include			"user.h"

int	 	Upload(int sockfd, User *user);
int	 	cloud_service(int sockfd);
int		Download(int sockfd, User *user);


/*		Main of Server		*/

int	main(int argc, char **argv) {
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;
	void				sig_chld(int);

	listenfd = Socket( AF_INET, SOCK_STREAM, 0 );
	bzero( &servaddr, sizeof(servaddr) );
	servaddr.sin_family			= AF_INET;
	servaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	servaddr.sin_port			= htons(SERV_PORT);

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr) );
	Listen(listenfd, LISTENQ);
	Signal(SIGCHLD, sig_chld);

	while(TRUE) {
		clilen = sizeof(cliaddr);
		if( (connfd = accept(listenfd, (SA *) &cliaddr, &clilen)) < 0) {
			if( errno == EINTR )
				continue;
			else
				err_sys("accept error\n");
		}

		/*		Create Child Process		*/

		if( (childpid = Fork()) == 0 ) {
			Close(listenfd);
			printf("process : %d : allocated!!\n", (int)getpid());
			cloud_service(connfd);
			Close(connfd);
			exit(SUCCESS);
		}
		Close(connfd);		/*		Parent closes connected socket		*/
	}
}


/*		(server) 서비스 선택 Func		*/

int cloud_service(int sockfd) {
	User 			user;
	boolean			first = TRUE;
	int				pid = (int)getpid();		
	time_t			start, end;

	start = time(NULL);

	if(s_user_ui(sockfd) != TRUE)
		puts("s_user_ui Error!!");

	while(TRUE) {
		recv_user(sockfd, &user);

		if(first) {
			Mkdir(user.user_id);
			first = FALSE;
		}
			
		if( (!strcmp(user.service , "1")) || (!strcmp(user.service, "upload")) ){
			printf("process : %d : ID : %s : Start Upload Service\n", 
					pid, user.user_id);
			Upload(sockfd, &user);
		}

		/*	download	*/

		else if( (!strcmp(user.service, "2")) || (!strcmp(user.service, "download")) ){
			printf("process : %d : ID : %s : Start Download Service\n", 
					pid, user.user_id);
			Download(sockfd, &user);
		}

		/*		Show List	*/

		else if( (!strcmp(user.service, "3")) || (!strcmp(user.service, "show")) ) {
			printf("process : %d : ID : %s : Start Show List Service\n", 
					pid, user.user_id);
			Show(sockfd, &user);
		}


		/*		exit		*/

		else if( (!strcmp(user.service, "4")) || (!strcmp(user.service, "exit")) ){
			printf("process : %d : ID : %s : Exit Service\n", 
					pid, user.user_id);
			end = time(NULL);
			printf("process : %d : ID : %s : Total time : %d sec\n",
				pid, user.user_id, (INT)(end - start));
			
			exit(0);
		}
	}

	end = time(NULL);
	printf("process : %d : ID : %s : Total time : %d sec\n",
			pid, user.user_id, (INT)(end - start));

	return SUCCESS;
}


/*		(server) Upload Func		*/

int Upload(int sockfd, User *user) {
	int				create;
	char			buf[MAXLINE];
	ssize_t			n;
	char*			ser_fd;
	int				pid = (int)getpid();
	
	ser_fd = s_fd(user->user_id, user->filename);
	create = open( ser_fd, O_WRONLY | O_CREAT | O_APPEND, DIR_PERMISSION);

	if( create == ERROR ) {
		perror("open");
		err_quit("open: Server terminated prematurely\n");
	}

again:
	while( ( n = read(sockfd, buf, MAXLINE) ) > 0 ) {
		if(!strcmp(buf, END_SIGNAL)){
			printf("process : %d : ID : %s : %s Upload Complete!!\n", 
					pid, user->user_id, user->filename);	
			break;;
		}
		Write(create, buf, MAXLINE);
		array_clear(buf, MAXLINE);
	}
	if( (n < 0) && (errno == EINTR) )
		goto again;
	else if( n < 0 )
		err_sys("Upload: read error\n");
	
	close(create);
	free(ser_fd);
	return SUCCESS;
}


/*		(server) Download Func		*/

int Download(int sockfd, User *user) {
	int			fd;
	char		buf[MAXLINE];

	fd = open(user->filename, O_RDONLY);
	if(fd == ERROR) {
		perror("open");
		exit(SUCCESS);
	}

	while( read(fd, &buf, MAXLINE) > 0 ) {
		Writen(sockfd, buf, MAXLINE);
		array_clear(buf, MAXLINE);
	}
	Writen(sockfd, END_SIGNAL, MAXLINE);

	return SUCCESS;
}

