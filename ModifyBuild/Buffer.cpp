#include "stdafx.h"
#include "Buffer.h"


Util::Buf::CBigBuffer::CBigBuffer() :
m_buf(NULL),
m_len(0),
m_alloc(0),
m_resize(TRUE)
{

}

Util::Buf::CBigBuffer::~CBigBuffer()
{
	if (m_buf)
	{
		delete m_buf;
		m_buf = NULL;
		m_len = 0;
		m_alloc = 0;
		m_resize = FALSE;
	}
}

Util::Buf::CBigBuffer::CBigBuffer(const CBigBuffer &obj) :
m_buf(NULL),
m_len(0),
m_alloc(0),
m_resize(TRUE)
{
	if (obj.m_len && obj.m_buf)
	{
		m_alloc = m_len = obj.m_len;
		m_buf = new UINT8[m_alloc];
		memcpy(m_buf, obj.m_buf, m_alloc);
	}
	m_resize = obj.m_resize;
}

Util::Buf::CBigBuffer& Util::Buf::CBigBuffer::operator = (const CBigBuffer &obj)
{
	if (this != &obj)
	{
		if (m_buf)
		{
			delete m_buf;
			m_buf = NULL;
			m_alloc = m_len = 0;
		}
		if (obj.m_len && obj.m_buf)
		{
			m_alloc = m_len = obj.m_len;
			m_buf = new UINT8[m_alloc];
			memcpy(m_buf, obj.m_buf, m_alloc);
		}
		m_resize = obj.m_resize;
	}
	return *this;
}

void Util::Buf::CBigBuffer::Attach(UINT8 *buf, UINT32 len)
{
	if (m_buf)
	{
		delete m_buf;
		m_buf = NULL;
		m_len = 0;
		m_alloc = 0;
		m_resize = FALSE;
	}
	m_buf = buf;
	m_len = len;
	m_resize = FALSE;
	m_alloc = len;
}

void Util::Buf::CBigBuffer::Deattach()
{
	m_buf = NULL;
	m_len = 0;
	m_alloc = 0;
	m_resize = TRUE;
}

BOOL Util::Buf::CBigBuffer::Append(UINT8 *buf, UINT32 len)
{
	if (NULL == buf || 0 == len)
	{
		return FALSE;
	}
	if ((m_len + len) > m_alloc)
	{
		if (FALSE == m_resize)
		{
			return FALSE;
		}
		m_alloc = (m_len + len) * 3 / 2;
		UINT8 *temp = new UINT8[m_alloc];
		if (m_buf && m_len)
		{
			memcpy(temp, m_buf, m_len);
		}
		if (m_buf)
		{
			delete m_buf;
		}
		m_buf = temp;
	}
	memcpy(m_buf + m_len, buf, len);
	m_len += len;
	return TRUE;
}

void Util::Buf::CBigBuffer::EraseLeft(UINT32 len)
{
	if (len >= m_len)
	{
		m_len = 0;
	}
	else
	{
		memmove(m_buf, m_buf + len, m_len - len);
		m_len -= len;
	}
}

void Util::Buf::CBigBuffer::EraseRight(UINT32 len)
{
	if (len >= m_len)
	{
		m_len = 0;
	}
	else
	{
		m_len -= len;
	}
}

void Util::Buf::CBigBuffer::Empty()
{
	m_len = 0;
}
