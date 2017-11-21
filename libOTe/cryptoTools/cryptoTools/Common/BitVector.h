#pragma once
// This file and the associated implementation has been placed in the public domain, waiving all copyright. No restrictions are placed on its use. 

#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Crypto/PRNG.h>
#include <cryptoTools/Common/BitIterator.h>
#include <cryptoTools/Common/ArrayView.h>
namespace osuCrypto {


    //class PRNG;

    class BitVector// : public ChannelBuffer
    {

        u8* mData;
        u64 mNumBits, mAllocBytes;

    public:

        typedef u8 value_type;
        typedef value_type* pointer;
        typedef u64 size_type;

        BitVector()
            :mData(nullptr),
            mNumBits(0),
            mAllocBytes(0)
        {}

        BitVector(u8* data, u64 length);

        
        BitVector(std::string data);

        explicit BitVector(size_t n)
            :mData(nullptr),
            mNumBits(0),
            mAllocBytes(0)
        {
            reset(n);
        }

        BitVector(const BitVector& K)
            :mData(nullptr),
            mNumBits(0),
            mAllocBytes(0)
        {
            assign(K);
        }

        BitVector(BitVector&& rref);

        ~BitVector() { delete[] mData; }

         

        void assign(const block& b);
        void assign(const BitVector& K); 

        void append(u8* data, u64 length, u64 offset = 0);
        void append(const BitVector& k) { append(k.data(), k.size()); }

        // erases original contents
        void reset(size_t new_nbits = 0);
        void resize(u64 newSize);
        void reserve(u64 bits);

        void copy(const BitVector& src, u64 idx, u64 length);

        u64 capacity() const { return mAllocBytes * 8; }
        u64 size() const { return mNumBits; }
        u64 sizeBytes() const { return (mNumBits + 7) / 8; }
        u8* data() const { return mData; }

        BitVector& operator=(const BitVector& K);
        BitReference operator[](const u64 idx) const;
        BitVector operator^(const BitVector& B)const;
        BitVector operator&(const BitVector& B)const;
        BitVector operator|(const BitVector& B)const;
        BitVector operator~()const;
        void operator^=(const BitVector& A);
        void operator&=(const BitVector& A);
        void operator|=(const BitVector& A);
        bool operator==(const BitVector& k) { return equals(k); }
        bool operator!=(const BitVector& k)const { return !equals(k); }

        bool equals(const BitVector& K) const;
         
        void fromString(std::string data);


        BitIterator begin() const;
        BitIterator end() const;
        void nChoosek(u64 n, u64 k, PRNG& prng);
        u64 hammingWeight() const;

        void pushBack(u8 bit);
        inline BitReference back() { return (*this)[size() - 1]; }

        void randomize(PRNG& G); 
        u8 parity();  

        std::string hex()const;



        template<class T>
        span<T> getArrayView() const;

        template<class T>
        gsl::span<T> getSpan() const;



    };

    template<class T>
    inline span<T> BitVector::getArrayView() const
    {
        return span<T>((T*)mData, (T*)mData + (sizeBytes() / sizeof(T)));
    }

    template<class T>
    inline gsl::span<T> BitVector::getSpan() const
    {
        return gsl::span<T>((T*)mData, (T*)mData + (sizeBytes() / sizeof(T)));
    }

    std::ostream& operator<<(std::ostream& in, const BitVector& val);


    template<>
    inline u8* channelBuffData<BitVector>(const BitVector& container)
    {
        return (u8*)container.data();
    }

    template<>
    inline BitVector::size_type channelBuffSize<BitVector>(const BitVector& container)
    {
        return container.sizeBytes();
    }

    template<>
    inline bool channelBuffResize<BitVector>(BitVector& container, u64 size)
    {
        return size == container.sizeBytes();
    }

}