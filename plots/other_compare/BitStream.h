#ifndef __BIT_STREAM_H__
#define __BIT_STREAM_H__

#include <iostream>
#include <fstream>

namespace alex { namespace io { namespace binary
{
    class BitStreamWriter
    {
    public:
        BitStreamWriter(std::ostream& s) : _s(s), _bitBuffer(0), _bitCount(0) {};

        int byteAlign(void)
        {
            int v = _bitBuffer;
            if (_bitCount != 0)
            {
                _bitBuffer <<= 8 - (_bitCount);
                _s.put(_bitBuffer);
            }

            _bitBuffer = _bitCount = 0;
            return v;
        };

        int flushOutput(unsigned char onesFill)
        {
            int v = -1;
            if (_bitCount != 0)
            {
                _bitBuffer <<= (8 - _bitCount);
                if (onesFill)
                    _bitBuffer |= (0xFF >> _bitCount);

                _s.put(_bitBuffer);
                v = _bitBuffer;
            }

            _bitBuffer = _bitCount = 0;
            return v;
        };

        void putChar(int c)
        {
            if (_bitCount == 0)
            {
                _s.put(c);
            }
            else
            {
                int tmp = (c & 0xFF) >> _bitCount;
                tmp = tmp | ((_bitBuffer) << (8 - _bitCount));
                _s.put((char)tmp);
                _bitBuffer = (char)c;
            }
        };

        void putBit(bool c)
        {
            _bitCount++;
            _bitBuffer <<= 1;

            if (c != 0)
            {
                _bitBuffer |= 1;
            }

            if (_bitCount == 8)
            {
                _s.put(_bitBuffer);
                _bitCount = 0;
                _bitBuffer = 0;
            }
        };

    private:
        std::ostream& _s;
        char _bitBuffer;
        unsigned char _bitCount;
    };

    class BitStreamReader
    {
    public:
        BitStreamReader(std::istream& s) : _s(s), _bitBuffer(0), _bitCount(0) {};

        int getChar(void)
        {
            int v = _s.get();

            if (_bitCount == 0)
                return v;

            int tmp = (v >> _bitCount);
            tmp |= _bitBuffer << (8 - _bitCount);
            _bitBuffer = (char)v;

            return tmp & 0xFF;
        };

        int getBit(void)
        {
            int v;
            if (_bitCount == 0)
            {
                v = _s.get();
                _bitCount = 8;
                _bitBuffer = v;
            }

            _bitCount--;
            v = _bitBuffer >> _bitCount;

            return v & 0x01;
        };

    private:
        std::istream& _s;
        char _bitBuffer;
        unsigned char _bitCount;
    };
}}}

#endif
