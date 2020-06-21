package multicastChat;

/*
 * KwangWoon University
 * 2019년도 1학기 객체지향프로그래밍실습 
 * 개인프로젝트
 * 전자통신공학과 2014707073 김수환
 * 주제 : 멀티캐스트 다중 채팅 프로그램
 * Class : SQL Query문 관련 클래스
 */

import java.awt.EventQueue;
import java.net.InetAddress;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

public class UserDao implements ChatInterface {
	Connection con;
	PreparedStatement pstmt;
	ResultSet rs;

	UserData user;
	ArrayList<UserData> userList;

	/* UserDao 생성자 */
	UserDao() {
		con = new OracleDBConnector().getCon();
		pstmt = null;
		rs = null;
		user = null;
		userList = null;
	}
	

	/* UserData 를 가지고 있는 ArrayList 를 반환 */
	public ArrayList<UserData> select() throws Exception {
		/* 날릴 Query 문 */
		String sql = "SELECT * FROM CUSTOMER";
		pstmt = con.prepareStatement(sql);
		rs = pstmt.executeQuery();
		userList = new ArrayList<>();
		
		/* Database Table에서 */
		/* id,pw,name을 받아와서 */
		/* UserData의 객체에 저장 */
		while (rs.next()) {
			user = new UserData();
			user.setId(rs.getString("ID"));
			user.setPw(rs.getString("PW"));
			user.setName(rs.getString("NAME"));
			userList.add(user);
		}
		return userList;
	}

	public boolean idAlreadyExist(String tf_JoinId) throws SQLException {
		/* 날릴 Query문 */
		String sql = "SELECT ID FROM CUSTOMER";
		pstmt = con.prepareStatement(sql);
		rs = pstmt.executeQuery();
		
		/* TABLE에서 ID들만 받아와서 검색 */
		while (rs.next()) {
			/* 넘겨받은 ID와 같으면 true 반환 */
			if (tf_JoinId.equals(rs.getString("ID"))) {
				return true;
			}
		}
		/* 넘겨받은 ID와 다르면 false 반환 */
		return false;
	}

	/* 회원가입에 성공하게 된다면 발생되는 메서드 */
	public int insert(String id, String pw, String name) {
		int loginOk;
		try {
			String sql = "INSERT INTO CUSTOMER VALUES ('" + id + "','" + pw + "','" + name + "')";
			pstmt = con.prepareStatement(sql);
			loginOk = pstmt.executeUpdate();
		} catch (Exception e) {
			return EXCEPTION_OCCUR;
		}
		return loginOk;
	}

	/* 회원가입되었는지 확인하기 위하여 만든 메서드 */
	public boolean loginCheck(String id, String pw) throws Exception {
		userList = this.select(); /* 모든 id, pw data를 저장 */
		for (UserData user : userList) { // 돌면서 일치하는 data가 있는지 확인
			if (id.equals(user.getId()) && pw.equals(user.getPw()))
				return true;
		}
		return false;
	}

	/* 로그인을 성공했을때 발생 */
	public void loginSuccess(String id) throws Exception {
		for (UserData user : userList) {
			if (id.equals(user.getId())) {
				String loginName = user.getName();
				
				EventQueue.invokeLater(new Runnable() {
					public void run() {
						try {
							/* IP 주소(224.0.0.1 ~ 239.255.255.255) 및 표준 UDP 포트 번호로 지정 => 중요함 */
							InetAddress address = InetAddress.getByName(MULTICAST_IP); // 멀티캐스트 그룹 규칙!!
							new Messenger(id, loginName, address, PORT);
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				});

				break;
			}
		}
	}
}