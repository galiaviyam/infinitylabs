/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Tree - OOD              */
/*   Date:      03/05/23                */
/*   Reviewer:  Gal                     */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_TREE_HPP
#define ILRD_RD136_7_TREE_HPP

#include <list>     //list
#include <string>	// string

namespace ilrd
{
class Tree
{
public:
	Tree(const std::string& dirName);
	void Print() const;

private:	
	class FileComponent
	{
	public:
		FileComponent();
        virtual ~FileComponent();

		virtual void Print(size_t offset) const =0;

	protected:
		FileComponent(const FileComponent& src);
	
	private:
		FileComponent& operator=(const FileComponent& other);
	};

	class LeafFile: public FileComponent
	{
	public:
		LeafFile(const std::string& fileName);
		~LeafFile();
		
		void Print(size_t offset) const;
		
	private:
	    std::string m_fileName;
	};

	class CompositeFolder: public FileComponent
	{
	public:
		CompositeFolder(const std::string &dirPath);
		~CompositeFolder();

		void Add(FileComponent *fileName);
		void Print(size_t offset) const;

	private:
		std::list<const FileComponent*> m_list;
	    std::string m_dirName;
		static void DeleteList(FileComponent *FileComponent);
	};

    CompositeFolder m_root;
    static void PrintOffset(std::size_t offset);
    static FileComponent *RecAdd(const std::string& path, const std::string& curr);
};

} // ilrd

#endif	// ILRD_RD136_7_TREE_HPP

