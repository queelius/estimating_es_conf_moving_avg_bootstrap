#include <queue>
#include <map>
#include <iterator>
#include <algorithm>
#include <sstream>
#include "BinaryIO.h"
#include "BitStream.h"

namespace alex { namespace compression
{
    template <class T> class Huffman
    {
    public:
        typedef std::vector<bool> HuffCode;
        typedef std::map<T, HuffCode> HuffCodeMap;

        Huffman() {};

        Huffman(const std::vector<T>& message)
        {
            makeCodes(message);
        };

        void makeCodes(const std::vector<T>& message)
        {
            this->message = message;
            std::map<T, size_t> freq;

            for (const auto& token : message)
            {
                freq[token]++;
            }

            INode* root;
            root = buildTree(freq);
            makeCodesHelper(root, HuffCode(), codes);

            delete root;
        };

        HuffCodeMap getCodeMap() const
        {
            return codes;
        };

        std::string toStringCodeMap() const
        {
            std::stringstream ss;
            for (HuffCodeMap::const_iterator i = codes.begin(); i != codes.end(); ++i)
            {
                ss << i->first << " ";
                std::copy(i->second.begin(), i->second.end(),
                          std::ostream_iterator<bool>(ss));
                ss << std::endl;
            }
            return ss.str();
        };

    protected:
        struct INode
        {
            const size_t f;
            virtual ~INode() {}
            INode(size_t f) : f(f) {}
        };

        struct InternalNode : public INode
        {
            const INode* left;
            const INode* right;

            InternalNode(INode* child0, INode* child1) :
                INode(child0->f + child1->f), left(child0), right(child1) {};

            ~InternalNode()
            {
                delete left;
                delete right;
            };
        };

        struct LeafNode : public INode
        {
            const T token;
            LeafNode(size_t f, const T& token) : INode(f), token(token) {}
        };

        INode* buildTree(const std::map<T, size_t>& freq)
        {
            struct NodeCmp
            {
                bool operator()(const INode* lhs, const INode* rhs) const
                {
                    return lhs->f > rhs->f;
                };
            };

            std::priority_queue <INode*, std::vector<INode*>, NodeCmp> trees;
            for (const std::pair<T, size_t>& e : freq)
            {
                trees.push(new LeafNode(e.second, e.first));
            }
            while (trees.size() > 1)
            {
                INode* childR = trees.top();
                trees.pop();

                INode* childL = trees.top();
                trees.pop();

                INode* parent = new InternalNode(childR, childL);
                trees.push(parent);
            }
            return trees.top();
        }

        void makeCodesHelper(const INode* node, const HuffCode& prefix,
                             HuffCodeMap& outCodes)
        {
            if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
            {
                outCodes[lf->token] = prefix;
            }
            else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
            {
                HuffCode leftPrefix = prefix;
                leftPrefix.push_back(false);
                makeCodesHelper(in->left, leftPrefix, outCodes);

                HuffCode rightPrefix = prefix;
                rightPrefix.push_back(true);
                makeCodesHelper(in->right, rightPrefix, outCodes);
            }
        };

        HuffCodeMap codes;
        std::vector<T> message;
    };

    class HuffmanCharacterCode: public Huffman<char>
    {
    public:
        HuffmanCharacterCode() {};

        HuffmanCharacterCode(const std::string& message)
        {
            makeCodes(message);
        };

        void makeCodes(const std::string& message)
        {
            Huffman<char>::makeCodes(std::vector<char>(message.begin(), message.end()));
        };

        void read(std::istream& is)
        {
            alex::io::binary::BitStreamReader in(is);
            size_t numCodes = alex::io::binary::readU8(is);
            for (size_t i = 0; i < numCodes; ++i)
            {
                char c = is.get();
                size_t numBits = alex::io::binary::readU8(is);
                for (size_t j = 0; j < numBits; ++j)
                {
                    in.getBit();
                }
            }
        };

        void write(std::ostream& os)
        {
            alex::io::binary::BitStreamWriter out(os);
            alex::io::binary::writeU8(os, (uint8_t)codes.size());
            for (auto code : codes)
            {
                os.put(code.first);
                alex::io::binary::writeU8(os, (uint8_t)code.second.size());
                for (auto b : code.second)
                    out.putBit(b);
            }


        };
    };
}}