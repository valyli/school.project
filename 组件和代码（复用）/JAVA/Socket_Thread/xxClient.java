import java.io.*;
import java.net.*;

public class xxClient
	{
   static opendata od;
   public static boolean modDBinf(String modinf)
	{
	   /*
	   String sql = "insert into t_chatroom(nick,sex,color,ttime,nnote) values (?,?,?,?,?)";
 		String args[] = {nick,sex,color,time,note};
  		dbBridge.execSQL(sql, args);
		*/
	   String sql ="insert into xxinft (inf) values (?)";
	   try
	   {
		String args[]={modinf};
	   	od.dbBridge.execSQL(sql,args);
		return true;
	   }
	   catch (Exception e)
	   {
		   System.out.println(e.getMessage());
		   return false;
	   }
   }

   public static boolean goDBinf(String modinf)
	{
	   if(od.openDBinf())
	   {
		 if(modDBinf(modinf))
		   {
			 return true;
		   }
		   else
		   {
			   return false;
		   }
	   }
	   else
		{
		   return false;
	   }
   }

   public static void main (String args[])
	   {
       String server="";//������
       int port=0;//�˿�
	   String xxINF="";//��Ϣ����
	/////////////////////////////////////// ��ȡ�����в���
       if (args.length != 3)
		   {
            System.out.println ("Invalid number of paramaters");
			System.exit(1);
			}
	   else
		{
			server = new String(args[0]);			
           if(server.trim()=="")
			   {
				server="localhost";
				System.out.println("server = localhost (default)");
			   }

			try 
			{
				port = Integer.parseInt(args[1]);
			}
			catch (Exception e)
			 {
				System.out.println("server port = 1500 (default)");
				port = 1500;
			}

			xxINF = new String(args[2]);
			if(xxINF.trim() == ""||xxINF.trim() == null||xxINF.trim() == " ")//�ؼ�����xxINF����Ϊ�����˳�����
			{
				System.out.println ("NO INF");
				System.exit(1);
			}

			System.out.println (server + " " + port + " " + xxINF);

        }
   /////////////////////////////////////////��ȡ�����в�������
        try{
             System.out.println ("Connecting to " + server);
			 System.out.println ("....................") ;

             // ���������������
	     Socket xxSocket = new Socket(server, port);
		String INF = xxINF;

		 if(goDBinf(INF))	 //������Ϣ�룬�ı��豸�б�״̬
			{
			 //�������������
	     PrintStream xxout = new PrintStream(xxSocket.getOutputStream());
         DataInputStream xxin = new DataInputStream(xxSocket.getInputStream());
		 //����Ϣ��xxINF֪ͨxxServer�豸״̬�ı䣬��Ҫ���������ƥ��
            System.out.println(xxin.readLine());
			xxout.println(INF.trim());
			System.out.println (xxin.readLine());
			
			//Ԥ���˶����Ϣ���ݵĻ��ƣ��������Ӵ���
			//......
			//�����Ϣ����

			//��֪�������Ҫ�������λỰ
			xxout.println("EXIT");
			System.out.println (xxin.readLine());
             xxout.close();
             xxin.close();
			}
		else
		{
			System.out.println("goDBinf failed.");
		}
             System.out.println("close the connection.");
            //�ر��������������
            xxSocket.close();
	}
	catch (Exception e )
		{
            System.out.println (e);
		}
    }
}