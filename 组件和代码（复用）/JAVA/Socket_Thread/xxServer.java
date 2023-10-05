import java.net.*;
import java.io.*;

public class xxServer {

	static opendata od;//引入数据库连接对象

    public static void main(String args[])
	{
	int port;        //缺省为1500
	ServerSocket server_socket;
	BufferedReader input;
///获取端口设置信息
	try
	{
	    port = Integer.parseInt(args[0]);
	}
	catch (Exception e)
	{
	    System.out.println("port = 1500 (default)");
	    port = 1500;
	}
///获取端口设置信息结束
		try
		{
			//开始监听port
	    server_socket = new ServerSocket(port);
	    System.out.println("xxServer waiting for client on port " + server_socket.getLocalPort());

			 //打开数据库连接
		od=new opendata();
		od.openDBinf();
		         //服务程序启动时启动一个长期存在并且检测时间匹配的线程
		 		//线程内不停的循环，检测时间，条件激活
	   			try
				{
					new xxTimeThread(od);
				}
				catch (Exception e) 
				{
					 System.out.println(e);
				}
  		
		//不停的循环，用于接受客户端的请求
		String ThreadID;
	    while(true) 
			{
				Socket socket = server_socket.accept();
				//以响应时间作为线程ID
				jspcalendar wo=new jspcalendar();
				ThreadID=wo.getnowtime();
				new xxServerThread(socket,ThreadID).start();//开子线程处理事件驱动
				System.out.println("New client accepted " +socket.getInetAddress()+ ":" + socket.getPort());

				//new xxTimeThread(od);//开子线程处理时间驱动
				//检测时间
            }
		}
		catch (Exception e) 
			{
				 System.out.println(e);
			}
    }
}

class xxTimeThread implements Runnable 
{
	Thread t;
	opendata od;
	String xxtime;
	Thread TimeThread;
	public xxTimeThread(opendata xxod)
	{
		od=xxod;
		TimeThread = new Thread(this);
		TimeThread.start();
		TimeThread.setPriority(Thread.NORM_PRIORITY - 3);

	}
	public void run()
	{
		while(true)
			{
				try
				{
				jspcalendar wo=new jspcalendar();
				xxtime=wo.getnowtime();
				System.out.println(xxtime + " --test xxTimeThread");
				System.out.println(TimeThread.getPriority() + " --test xxTimeThread");
					TimeThread.sleep(10000);
					if (wo.getDayOfMonth()==16)
					{
						matching_B_1();
					}

				}
				catch (Exception e) 
				{
					 System.out.println(e);
				}
				
			}
	}
		
	public boolean matching_B_1()//匹配条件B_1：检查今天是否是一号，如果是，则检查3表，并将信息通过邮件发送
	{
		System.out.println("matching_B_1 exec");
		return true;
	}
}

class xxServerThread extends Thread
	{
    private Socket xxSocket;
    private String xxThreadID;
    public xxServerThread(Socket socket,String ThreadID)
	{
        xxSocket=socket;
		xxThreadID=ThreadID;
    }
    public void run()
		{
        try
			{
             BufferedReader inReader=new BufferedReader(new InputStreamReader(xxSocket.getInputStream() ));
             PrintWriter outWriter=new PrintWriter(xxSocket.getOutputStream(),true);

             outWriter.println("Welcome to xxserver! your Thread ID is "+xxThreadID);
			outWriter.println(Thread.currentThread().getPriority() + " --test xxServerThread");

             String in="";
             in=inReader.readLine();
             while(!in.trim().equals("EXIT")){
                 outWriter.println("Echo ("+xxThreadID+"):"+in+" @ "+xxSocket.getLocalPort());
                 in=inReader.readLine();
             }
             outWriter.println("BYE client ("+xxThreadID+")");
             xxSocket.close();
             System.out.println("client ("+xxThreadID+") closed");
        }
		catch(Exception e)
			{
            System.out.println(e);
			}
    }
//A类为事件驱动条件匹配
//B类为时间驱动条件匹配
	public boolean matching_A_1()//匹配条件A_1：微波炉开，如果空调开着，则关闭空调
		{
			return true;
		}

}