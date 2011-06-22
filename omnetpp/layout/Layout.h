//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "../General.h"
/*  An example data layout in a window:
 *
 *  If the data layout parameters are set to be:
 *  windowSize = (256 + 512 + 128) * 1024
 *  serverNum = 3
 *  serverList[3] = {1, 3, 9}
 *  serverShares[3] = {256*1024, 512*1024, 128*1024}
 *
 *  The following chart depicts the data layout:
 *  [<-server1,256KB->|<-server3,512KB->|<-server9,128KB->]
 *  | <-------------  windowSize: 896KB   --------------> |
 *
 *  The following is an example window structure in the requested data
 *  (this is only determined by the data size of the request):
 *  [ window0,896KB | window1,896KB | window2,896KB | window3,39KB ]
 *  | <----------------- Data Size 2727KB -----------------------> |
 */


class Layout : public cSimpleModule{
private:
	int appId;
	long windowSize; // The size of the data in a window.
	int serverNum; // Number of DServer storing this requested data.
	int serverList[MAX_DS_NUM]; // The list of DServer indexes storing this requested data.
	long serverShares[MAX_DS_NUM]; // The size of data in a window on each server.
public:
	Layout(int id);
	virtual ~Layout();
	virtual void setWindowSize(long size);
	virtual void setServerNum(int num);
	virtual void setServerList(int servernum, int list[]);
	virtual void setServerShares(int servernum, long size[]);
	virtual void setLayout(qPacket *);
	virtual void setqPacket(qPacket *);
	virtual void setServerID(int index, int serverID);
	virtual void setServerShare(int index, long share);
	virtual int getAppID();
	virtual long getWindowSize();
	virtual int getServerNum();
	virtual int getServerID(int index); // The input index is the index in the serverList or serverShares.
	virtual long getServerShare(int index); // The input index is the index in the serverList or serverShares.
	virtual int findServerIndex(int id); // Find a server's index in the list given its ID.
	virtual void calculateWindowSize();
};

#endif /* LAYOUT_H_ */