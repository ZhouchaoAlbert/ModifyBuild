#ifndef  __BUFFER_H__
#define  __BUFFER_H__
#include <Windows.h>
#include <tchar.h>
namespace Util
{
	 namespace Buf
	{
		 class  CBigBuffer
		 {
		 public:
			 CBigBuffer();
			 ~CBigBuffer();
			 CBigBuffer(const CBigBuffer &obj);
			 CBigBuffer& operator = (const CBigBuffer &obj);
			 operator UINT8*(){ return m_buf; }
			 operator UINT32(){ return m_len; }
		 public:
			 void Attach(UINT8 *buf, UINT32 len);
			 void Deattach();
		 public:
			 BOOL Append(UINT8 *buf, UINT32 len);
			 void EraseLeft(UINT32 len);
			 void EraseRight(UINT32 len);
			 void Empty();
			 UINT8* GetBuf(){ return m_buf; }
			 UINT32 GetLen(){ return m_len; }
		 protected:
		 private:
			 UINT8 *m_buf;
			 UINT32 m_len;
			 UINT32 m_alloc;
			 BOOL m_resize;
		 };
	}
}
#endif


