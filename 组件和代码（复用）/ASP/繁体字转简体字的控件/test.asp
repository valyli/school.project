<%@ Language=VBScript %>
<HTML>
<BODY>
<%
Dim obj
Set obj = Server.CreateObject("BigToGB.Big2GB")
Response.Write  obj.GBTOBIG("���Ĳ���:��GB��BIG5") 
Response.Write "<br>"
Response.Write  obj.BIGTOGB("�������:�qBIG5��GB")
%>
</BODY>
</HTML>


