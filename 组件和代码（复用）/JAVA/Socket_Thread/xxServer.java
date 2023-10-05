import java.net.*;
import java.io.*;

public class xxServer {

	static opendata od;//�������ݿ����Ӷ���

    public static void main(String args[])
	{
	int port;        //ȱʡΪ1500
	ServerSocket server_socket;
	BufferedReader input;
///��ȡ�˿�������Ϣ
	try
	{
	    port = Integer.parseInt(args[0]);
	}
	catch (Exception e)
	{
	    System.out.println("port = 1500 (default)");
	    port = 1500;
	}
///��ȡ�˿�������Ϣ����
		try
		{
			//��ʼ����port
	    server_socket = new ServerSocket(port);
	    System.out.println("xxServer waiting for client on port " + server_socket.getLocalPort());

			 //�����ݿ�����
		od=new opendata();
		od.openDBinf();
		         //�����������ʱ����һ�����ڴ��ڲ��Ҽ��ʱ��ƥ����߳�
		 		//�߳��ڲ�ͣ��ѭ�������ʱ�䣬��������
	   			try
				{
					new xxTimeThread(od);
				}
				catch (Exception e) 
				{
					 System.out.println(e);
				}
  		
		//��ͣ��ѭ�������ڽ��ܿͻ��˵�����
		String ThreadID;
	    while(true) 
			{
				Socket socket = server_socket.accept();
				//����Ӧʱ����Ϊ�߳�ID
				jspcalendar wo=new jspcalendar();
				ThreadID=wo.getnowtime();
				new xxServerThread(socket,ThreadID).start();//�����̴߳����¼�����
				System.out.println("New client accepted " +socket.getInetAddress()+ ":" + socket.getPort());

				//new xxTimeThread(od);//�����̴߳���ʱ������
				//���ʱ��
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
		
	public boolean matching_B_1()//ƥ������B_1���������Ƿ���һ�ţ�����ǣ�����3��������Ϣͨ���ʼ�����
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
//A��Ϊ�¼���������ƥ��
//B��Ϊʱ����������ƥ��
	public boolean matching_A_1()//ƥ������A_1��΢��¯��������յ����ţ���رտյ�
		{
			return true;
		}

}