<%@ Language=VBScript %>
<HTML>
<BODY>
<%
Dim obj
Set obj = Server.CreateObject("BigToGB.Big2GB")
Response.Write  obj.GBTOBIG("中文测试:从GB到BIG5") 
Response.Write "<br>"
Response.Write  obj.BIGTOGB("いゅ代刚:眖BIG5GB")
%>
</BODY>
</HTML>


