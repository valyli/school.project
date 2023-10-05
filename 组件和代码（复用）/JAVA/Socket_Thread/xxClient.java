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
       String server="";//服务器
       int port=0;//端口
	   String xxINF="";//信息参数
	/////////////////////////////////////// 提取命令行参数
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
			if(xxINF.trim() == ""||xxINF.trim() == null||xxINF.trim() == " ")//关键参数xxINF参数为空则退出程序
			{
				System.out.println ("NO INF");
				System.exit(1);
			}

			System.out.println (server + " " + port + " " + xxINF);

        }
   /////////////////////////////////////////提取命令行参数结束
        try{
             System.out.println ("Connecting to " + server);
			 System.out.println ("....................") ;

             // 与服务器建立连接
	     Socket xxSocket = new Socket(server, port);
		String INF = xxINF;

		 if(goDBinf(INF))	 //分析信息码，改变设备列表状态
			{
			 //建立输入输出流
	     PrintStream xxout = new PrintStream(xxSocket.getOutputStream());
         DataInputStream xxin = new DataInputStream(xxSocket.getInputStream());
		 //用信息码xxINF通知xxServer设备状态改变，需要重新与规则匹配
            System.out.println(xxin.readLine());
			xxout.println(INF.trim());
			System.out.println (xxin.readLine());
			
			//预留了多次信息传递的机制，便与今后复杂处理
			//......
			//多次信息传送

			//告知服务程序要结束本次会话
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
            //关闭与服务器的连接
            xxSocket.close();
	}
	catch (Exception e )
		{
            System.out.println (e);
		}
    }
}