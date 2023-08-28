/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Tree - OOD              */
/*   Date:      03/05/23                */
/*   Reviewer:  Gal                     */
/*                                      */
/****************************************/

#include <iostream>     //cout
#include <cstring>      //strcmp
#include <algorithm>    //for_each
#include <dirent.h>     //dirent
#include <sys/stat.h>   //stat

#include "tree.hpp"     //tree header file

namespace ilrd
{
/*------------------------------- Tree --------------------------------*/
Tree::Tree(const std::string& dirName) : m_root(dirName)
{    
}

void Tree::Print() const
{
    m_root.Print(0);
}

void Tree::PrintOffset(size_t offset) 
{
    for (std::size_t i = 0; i < offset; ++i)
    {
        std::cout << "-->" << '\t' ;
    }
}

/*---------------------------- FileComponent ----------------------------*/
Tree::FileComponent::FileComponent()
{
}

Tree::FileComponent::~FileComponent()
{
}
Tree::FileComponent::FileComponent(const FileComponent& src) { (void)src; }

/*---------------------------- LeafFile -----------------------------*/
Tree::LeafFile::LeafFile(const std::string& fileName) : 
                                    Tree::FileComponent(), m_fileName(fileName)
{

}

Tree::LeafFile::~LeafFile()
{
}

void Tree::LeafFile::Print(size_t offset) const
{
    Tree::PrintOffset(offset);
    std::cout << m_fileName << std::endl;
}

/*---------------------------- CompositeFolder -----------------------------*/
Tree::CompositeFolder::CompositeFolder(const std::string &dirPath) : m_dirName(dirPath)
{
	DIR *dir = 0;
	dirent *entry;
	std::size_t first_chars = 2;
	
	dir = opendir(dirPath.c_str());
	if (dir)
	{
		while ((entry = readdir(dir)))
		{
			if (0 != strncmp(entry->d_name, "..", first_chars) 
				&& 0 != strncmp(entry->d_name, ".", 1))
			{
				if (DT_DIR == entry->d_type)
				{
					CompositeFolder *tmp = new CompositeFolder(dirPath + "/" + entry->d_name);
					Add(tmp);
				}
				else
				{
					LeafFile *tmp = new LeafFile(entry->d_name);
					Add(tmp);
				}
			}
		}
		closedir(dir);
	}
}

void Tree::CompositeFolder::DeleteList(Tree::FileComponent *FileComponent)
{
    delete FileComponent;
}

Tree::CompositeFolder::~CompositeFolder()
{
    std::list<const FileComponent *>::const_iterator iter;
	iter = m_list.begin();
	while (m_list.end() != iter)
	{
		std::list<const FileComponent *>::const_iterator tmp = iter;
		++iter;
		delete *tmp;
	}
}

void Tree::CompositeFolder::Add(FileComponent *fileName)
{
    m_list.push_back(fileName);
}

void Tree::CompositeFolder::Print(size_t offset) const
{
    Tree::PrintOffset(offset);
    std::for_each(m_list.begin(), m_list.end(),
    std::bind2nd(std::mem_fun(&Tree::FileComponent::Print), (offset + 1)));
}
} //namespace ilrd;

