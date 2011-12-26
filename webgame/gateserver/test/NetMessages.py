# -*- coding: utf-8 -*- 
class Packets:
        DEF_MSGTYPE_CONFIRM = 0x0000 
	DEF_MSGTYPE_REJECT = 0x0001

	MSGID_REQUEST_LOGIN = 0x00000001
	MSGID_RESPONSE_LOGIN = 0x10000001

	MSGID_REQUEST_ENTERGAME = 0x00000002
	MSGID_RESPONSE_ENTERGAME = 0x10000002

	MSGID_REQUEST_SWITCHSCENE = 0x00000009
	MSGID_RESPONSE_SWITCHSCENE = 0x10000009
	
	MSGID_REQUEST_LEAVEGAME = 0x00000004
        MSGID_RESPONSE_LEAVEGAME = 0x10000004

	MSGID_REQUEST_NEWACCOUNT = 0x00000008
        MSGID_RESPONSE_NEWACCOUNT = 0x10000008

	MSGID_REQUEST_NEWCHARACTER = 0x00000010
        MSGID_RESPONSE_NEWCHARACTER = 0x10000010

	MSGID_REQUEST_GETCHARLIST = 0x00000011
        MSGID_RESPONSE_GETCHARLIST = 0x10000011

	MSGID_REQUEST_BINDGS = 0x00000111
	MSGID_RESPONSE_BINDGS = 0x10000111

	MSGID_REQUEST_JOINSCENE = 0x00000003
	MSGID_RESPONSE_JOINSCENE = 0x10000003

	MSGID_REQUEST_SYNPOS =  0x00010002
	MSGID_RESPONSE_SYNPOS = 0x10010002
	MSGID_NOTIFY_SYNPOS =  0x00110002
	MSGID_SCENE_FRAME = 0x01110001
        MSGID_NOTIFY_LEAVEAOI = 0x00120002
        MSGID_NOTIFY_ENTERAOI = 0x00130002

        MSGID_REQUEST_SAVEARCHIVE = 0x00150002

        #客户端通知初始化完成可以接收场景信息
        MSGID_C2SNOTIFY_READY = 0x00140002

	#for gs
	MSGID_REQUEST_REGGS = 0x01000001
	MSGID_RESPONSE_REGGS = 0x11000001
	#转发消息
	MSGID_REQUEST_DATA2GS = 0x0000000F
	MSGID_RESPONSE_DATA2GS = 0x1000000F
	MSGID_REQUEST_DATA2CLIENTS = 0x000000FF
	#for test
	MSGID_REQUEST_ECHO = 0x000000FF
	MSGID_RESPONSE_ECHO = 0x100000FF

	#sqlstore
	MSGID_REQUEST_EXECSQL = 0x0000002F
	MSGID_RESPONSE_EXECSQL = 0x1000002F
	MSGID_REQUEST_EXECPROC = 0x0000003F
	MSGID_RESPONSE_EXECPROC = 0x1000003F
	MSGID_REQUEST_QUERY = 0x0000004F
	MSGID_RESPONSE_QUERY = 0x1000004F
	#disconnect
	MSGID_NOTIFY_DISCONNECT = 0x11111111

	DEF_LOGRESMSGTYPE_PASSWORDMISMATCH = 0x0001
	DEF_LOGRESMSGTYPE_NOTEXISTINGACCOUNT = 0x0002
	DEF_LOGRESMSGTYPE_NOTEXISTINGCHARACTER = 0x003
 
	DEF_ENTERGAMEMSGTYPE_NEW = 0x0F1C

	DEF_ENTERGAMERESTYPE_PLAYING = 0x0F20
	DEF_ENTERGAMERESTYPE_REJECT = 0x0F21
	DEF_ENTERGAMERESTYPE_CONFIRM = 0x0F22
	DEF_ENTERGAMERESTYPE_FORCEDISCONN = 0x0F23

