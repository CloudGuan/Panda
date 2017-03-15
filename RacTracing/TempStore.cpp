#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<map>

#include "commonhead.h"
#include <set>
using namespace std;

//玩家剩余的包裹数目
const int spaceNum = 2;
//玩家包裹里水晶的数目
const int cryNum = 1;

//宝石的道具ID 
const int gemID = 799;
//水晶的道具ID 
const int crystalID = 800;
//小火龙的道具ID 
const int smallDragonID = 888;

static SActList gActList;

char LogStr[256];
/**
* \brief 发送提示给玩家
* @test 提示的内容
*/
void sendTextToUser(const string &text)
{
	cout << text << endl;
}
void GenerateTestData()
{
		///Avtivity one
	SActInfo mTmpAct;
	mTmpAct.nActID = 12;
	mTmpAct.DragList[1] = 2;
	mTmpAct.DragList[2] = 1;
	mTmpAct.PrizeList.push_back(SPrizeInfo(gemID,50));
	mTmpAct.PrizeList.push_back(SPrizeInfo(crystalID,10));
	mTmpAct.nSumSpace = 4;
	
	SActInfo mTmpActAnother;
	mTmpActAnother.nActID = 5;
	mTmpActAnother.DragList[3] = 1;

	mTmpActAnother.DragList[1] = 1;
	mTmpActAnother.PrizeList.push_back(SPrizeInfo(crystalID,50));
	mTmpActAnother.nSumSpace = 2;
	
	gActList.tActivityList[mTmpActAnother.nActID] = mTmpActAnother;
	gActList.tActivityList[mTmpAct.nActID] = mTmpAct;
}
/**
* \brief 写日志到文件，以便查询相关错误日志信息
* @log 日志的内容
*/
void writeLog(const string &log)
{
	cout << "log:" << log << endl;
}

struct exchangeGem_CS
{
	exchangeGem_CS()
	{
		objThisIDA = 0;
		objThisIDB = 0;
	}
	int objThisIDA;//道具A的唯一ID
	int objThisIDB;//道具B的唯一ID
};

struct NExchangeMsg
{
	NExchangeMsg()
		:m_nActID(-1)
	{
	}
	int m_nActID;
	set<int> ItemList;
};

struct item
{
	int id;// 道具ID
	int thisid;//道具唯一ID 
	int aptitude;//资质	
};

/**
* \brief 玩家的包裹类
*/
struct package
{
	/**
	* \brief 获取包裹剩余空间
	* @return 包裹剩余空间数目
	*/
	int getSpaceNum(){ return spaceNum; }

	/**
	* \brief 添加道具进包裹
	* @itemID 道具ID
	* @itemNum 道具数目
	* @return 道具是否添加成功
	*/
	bool addItem(int itemID, int itemNum)
	{
		//中间有很长的代码，可能会返回false;
		sendTextToUser("添加道具成功");
		return true;
	}

	/**
	* \brief 从包裹里扣除道具
	* @itemID 道具ID
	* @return 道具是否扣除成功
	*/
	bool removeItem(int itemID)
	{
		//中间有很长的代码，可能会返回false;
		return true;
	}

	/**
	* \brief 从包裹里扣除道具
	* @thisid 道具指针
	* @return 道具是否扣除成功
	*/
	bool removeItem(item* m_item)
	{
		if (m_item == NULL) return false;
		itemMap.erase(m_item->thisid);
		delete m_item;
		m_item = NULL;
		return true;
	}

	/**
	* \brief 从包裹里扣除道具
	* @itemID 道具ID
	* @return 道具是否扣除成功
	*/
	int getItemNum(int itemID)
	{
		if (itemID == crystalID)
			return cryNum;
		return 0;
	}


	/**
	* \brief 从包裹里获取道具指针
	* @thisid 道具ID
	* @return 道具指针
	*/
	item* getItemByThisID(const int thisid)
	{
		std::map<int, item*>::iterator it = itemMap.find(thisid);
		if ((it != itemMap.end()) && (it->second != NULL))
			return it->second;
		return NULL;
	}

	bool addItem(item* m_item)
	{
		if (NULL == m_item || itemMap.find(m_item->thisid) != itemMap.end())
			return false;

		itemMap.insert(std::make_pair(m_item->thisid, m_item));
		return true;
	}

	std::map<int, item*> itemMap;
};

/**
* \brief 玩家类
*/
struct user
{
	package pack;
};

bool nExchangeGem(NExchangeMsg& cmd, user &m_user)
{
	auto Actptr = gActList.tActivityList.find(cmd.m_nActID);
	if (Actptr == gActList.tActivityList.end())
	{
		sprintf(LogStr, "Error: can't found action id: %d", cmd.m_nActID);
		sendTextToUser("交易异常，活动暂未开放！");
		writeLog(LogStr);
		return false;
	}

	vector<item*> mDragons;
	for (set<int>::iterator ptrIt = cmd.ItemList.begin(); ptrIt != cmd.ItemList.end(); ptrIt++)
	{
		item* mPtrDragon = m_user.pack.getItemByThisID(*ptrIt);
		if (!mPtrDragon)
		{
			sprintf(LogStr, "Error:Can't find  Item : %d",*ptrIt);
			writeLog(LogStr);
			return false;
		}
		if (mPtrDragon->id != smallDragonID)
		{
			sendTextToUser("请使用小火龙兑换!\n");
			return false;
		}
		mDragons.push_back(mPtrDragon);
	}

	map<int,int> DragLists;

	for (vector<item*>::iterator It = mDragons.begin(); It != mDragons.end(); It++)
	{
		DragLists[(*It)->aptitude]++;
	}
	if (DragLists != Actptr->second.DragList)
	{
		sendTextToUser("小火龙资质不符合！！");
		return false;
	}

	if (m_user.pack.getSpaceNum() < Actptr->second.nSumSpace)
	{
		sendTextToUser("您的背包空间不足!\n");
		return false;
	}

	for (vector<item*>::iterator It = mDragons.begin(); It != mDragons.end(); It++)
	{
		if (!m_user.pack.removeItem(*It))
		{
			sprintf(LogStr,"Remove Item Error: %d\n",(*It)->thisid);
			writeLog(LogStr);
			sendTextToUser("交易异常，请联络客服解决！");
			return false;
		}
	}
	
	auto It = Actptr->second.PrizeList.begin();
	auto endIt = Actptr->second.PrizeList.end();
	for (;It!=endIt;It++)
	{
		if (!m_user.pack.addItem(It->nPrizeID, It->nPrizeNum))
		{
			sprintf(LogStr, "Error: Add Item:%d Error!\n", It->nPrizeID);
			writeLog(LogStr);
			sendTextToUser("交易异常！！");
			return false;
		}
	}
	writeLog("交易成功，请查收奖励！");
	return true;
}

bool exchangeGem(exchangeGem_CS &cmd, user &m_user)
{
	int nThisIDA = cmd.objThisIDA;
	int nThisIDB = cmd.objThisIDB;
	if (nThisIDA == nThisIDB)
	{
		sendTextToUser("无两条资质为1的龙");
		return false;
	}
	item* dragonA = m_user.pack.getItemByThisID(nThisIDA);
	item* dragonB = m_user.pack.getItemByThisID(nThisIDB);
	if (!dragonA || !dragonB)
	{
		sendTextToUser("交易失败");
		writeLog("获取小龙失败，item指针为空");
		return false;
	}
	if (dragonA->id != smallDragonID || dragonB->id != smallDragonID)
	{
		sendTextToUser("无两条资质为1的龙");
		return false;
	}
	if (dragonA->aptitude != 1 || dragonB->aptitude != 1)
	{
		sendTextToUser("无两条资质为1的龙");
		return false;
	}
	if (m_user.pack.getSpaceNum()<2)
	{
		sendTextToUser("包裹空间不足");
		return false;
	}
	if (!m_user.pack.removeItem(dragonA))
	{
		sendTextToUser("交易失败");
		writeLog("扣除第一条小火龙失败");
		return false;
	}
	if (!m_user.pack.removeItem(dragonB))
	{
		sendTextToUser("交易失败");
		writeLog("扣除第二条小火龙失败");
		return false;
	}
	if (!m_user.pack.addItem(gemID, 100))
	{
		sendTextToUser("交易失败");
		writeLog("添加100个宝石失败");
		return false;
	}
	writeLog("玩家完成2条资质为1的小火龙交换100宝石");
	return true;
}

int main()
{
	//括号以内代码模拟 客户端消息发送到服务器解包以后，服务器处理逻辑的流程 返回0表示这个消息的处理逻辑结束 
	/* 添加道具
	* forExample
	* user m_user;
	* m_user.addItem(1,1);
	*/

	//下面代码可认为是 之前玩家添加相关道具的过程。
	user m_user;
	item* mDragonPtr;
	for (int i = 0; i < 10; i++)
	{
		mDragonPtr = new item();
		if (!mDragonPtr)
			return 0;

		mDragonPtr->thisid = (1000 + i);
		mDragonPtr->id = smallDragonID;
		mDragonPtr->aptitude = (i % 3) + 1;
		m_user.pack.addItem(mDragonPtr);
	}

	//添加流程结束	
	GenerateTestData();
	//客户端发起请求流程
	//exchangeGem_CS cmd;
	//cmd.objThisIDA = 1000;
	//cmd.objThisIDB = 1000;
	
	NExchangeMsg cmd;
	cmd.m_nActID = 1;
	cmd.ItemList.insert(1000);
	cmd.ItemList.insert(1001);
	cmd.ItemList.insert(1003);
	nExchangeGem(cmd, m_user);
	//服务器处理
	//exchangeGem(cmd, m_user);
	return 0;
}
