/**
 * <p>Title: project of xiongxiong.com</p>
 * <p>Description: xiong@chinadigipro.com</p>
 * <p>Copyright: Copyright (c) 2002</p>
 * <p>Company: xiongxiong.com</p>
 * @author littlebear
 * @version 1.0
 */

import java.util.*;

public class bearsCalendar
{
  Calendar calendar=null;
  //按bean写的
  public bearsCalendar()
  {
  }
////////////////////////////////////////////////////////////////
  public void setbearsCalendar()
  {
    calendar=Calendar.getInstance();
    Date trialTime=new Date();
    calendar.setTime(trialTime);
  }
  public void setbearsCalendar(Date date)
  {
    calendar=Calendar.getInstance();
    calendar.setTime(date);
  }
  public void setYear(int year)
  {
    calendar.set(Calendar.YEAR,year+1900);
  }
  public void setMonth(int month)
  {
    calendar.set(Calendar.MONTH,month-1);
  }
  public void setDay(int day)
  {
    calendar.set(Calendar.DAY_OF_MONTH,day);
  }
/////////////////////////////////////////////////////////////////////以上为set
  //////////////////////////////////////////////////////比较时间后
  public boolean after(bearsCalendar when)
  {
    if(calendar.after(when))
      return true;
    return false;

  }
  //////////////////////////////////////////////////////比较时间前
  public boolean before(bearsCalendar when)
  {
    if(calendar.before(when))
      return true;
    return false;
  }
/////////////////////////////////////////////////////////////////////以下为get

  ////////int 型时间分列表
  public int getTheintYear()//年
  {
    return calendar.get(Calendar.YEAR);
  }
  public int getTheintMonth()//月
  {
    return 1+calendar.get(Calendar.MONTH);
  }
  public int getTheintDay()//日
  {
    return calendar.get(Calendar.DATE);
  }
  public int getTheintHour()//时
  {
    return calendar.get(Calendar.HOUR_OF_DAY);
  }
  public int getTheintMinute()//分
  {
    return calendar.get(Calendar.MINUTE);
  }
  public int getTheintSecond()//秒
  {
    return calendar.get(Calendar.SECOND);
  }
  public int getTheintMillisecond()//毫秒
  {
    return calendar.get(Calendar.MILLISECOND);
  }

  public int getDayOfMonth()
  {
    return calendar.get(Calendar.DAY_OF_MONTH);
  }
  public int getDayOfYear()
  {
    return calendar.get(Calendar.DAY_OF_YEAR);

  }
  public int getWeekOfYear()
  {
    return calendar.get(Calendar.WEEK_OF_YEAR);
  }
  public int getWeekOfMonth()
  {
    return calendar.get(Calendar.WEEK_OF_MONTH);
  }
  public int getDayOfWeek()
  {
    return calendar.get(Calendar.DAY_OF_WEEK)-1;
  }
////////// int 型时间分列表结束

////////// String 型时间分列表开始
  public String getdetailsnowtime()//当前时间详细时间列表
  {
    return getTheintYear()+":"+getTheintMonth()+":"+getTheintDay()+":"+getTheintHour()+":"+
        getTheintMinute()+":"+getTheintSecond()+":"+getTheintMillisecond();
  }
  public String getnowtime()
  {
    return getTheintYear()+":"+getTheintMonth()+":"+getTheintDay()+":"+getTheintHour()+":"+
        getTheintMinute()+":"+getTheintSecond();
  }
  public String getsimplenowtime()
  {
    return getTheintYear()+":"+getTheintMonth()+":"+getTheintDay();
  }
///////// String 型时间分列表结束

////////// 数据库 时间分列表开始
  public String getMonth()//得到月份
  {
    int m=getTheintMonth();
    String[] months=new String[]{"01","02","03","04","05","06","07","08","09","10","11","12"};
    if(m>12)
      return "unknown Month";
    return months[m-1];
  }
  public int getDay()
  {
    return getTheintDay();
  }
  public String getWeekDay()//得到星期中第几天
  {
    int x=getDayOfWeek();
    String[] days=new String[]{"1","2","3","4","5","6","7"};
    if(x>7)
      return "unknown to Day";
    return days[x-1];
  }

  public String getYMD()//数据库中的 年月日
  {
    return getTheintYear()+"-"+getMonth()+"-"+getTheintDay();
  }

  public String getDMY()//数据库中的 日月年
  {
    return getTheintDay()+"/"+getMonth()+"/"+getTheintYear();
  }
  public String getHMS()//当前时间 小时 分 秒
  {
    return getTheintHour()+":"+getTheintMinute()+":"+getTheintSecond();
  }

////////// 数据库 时间分列表结束

/*
  public void add(int mount)
  {
    calendar.add(Calendar.DATE,mount);
  }
*/
}