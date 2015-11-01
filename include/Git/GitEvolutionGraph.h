#ifndef GITEVOLUTIONGRAPH_H
#define GITEVOLUTIONGRAPH_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QMap>

namespace Git {
class GitVersion;

class GitEvolutionGraph {
public:
    /**
     * Explicit default constructor
     * @brief Creates blank evolution graph
     */
    GitEvolutionGraph();

    /**
     * Explicit default constructor
     * @brief Creates evolution graph with set up filepath
     * @param filePath Path to the git repository on file system
     */
    GitEvolutionGraph( QString filePath );

    /**
     * void setVersions( QList<Git::GitVersion*> versions )
     * @brief Setter of list of versions
     * @param versions list of versions
     */
    void setVersions( QList<Git::GitVersion*> versions ) {
        this->versions = versions;
    }

    /**
     * QList<Git::GitVersion*> getVersions()
     * @brief Getter of list of versions
     * @return list of versions
     */
    QList<Git::GitVersion*> getVersions() {
        return this->versions;
    }

    /**
     * void setFilePath( QString filePath )
     * @brief Setter of path to the git repository on file system
     * @param filePath Path to the git repository on file system
     */
    void setFilePath( QString filePath ) {
        this->filePath = filePath;
    }

    /**
     * QString getFilePath()
     * @brief Getter of path to the git repository on file system
     * @return path to the git repository on file system
     */
    QString getFilePath() {
        return this->filePath;
    }

    /**
     * Git::GitVersion* getVersion( int position )
     * @brief Getter of specific version in list of versions
     * @param position Index of version in list of versions
     * @return Specific versions from list
     */
    Git::GitVersion* getVersion( int position ) {
        return this->versions.at( position );
    }

    /**
     * int getLifespan()
     * @brief Returns lifespan of deleted files in graph
     * @return lifespan of deleted files in graph
     */
    int getLifespan() {
        return this->lifespan;
    }

    /**
     * void setLifespan( int lifespan )
     * @brief Sets a lifespan of deleted files in graph
     * @param lifespan Lifespan of deleted files in graph
     */
    void setLifespan( int lifespan ) {
        this->lifespan = lifespan;
    }

    /**
     * QMap<QString, int> getRemovedFiles()
     * @brief Returns map, where key is deleted file path in project and value version, in which was deleted
     * @return map, where key is deleted file path in project and value version, in which was deleted
     */
    QMap<QString, int> getRemovedFiles() {
        return this->removedFiles;
    }

    /**
     * void addRemovedFiles( QStringList list, int version )
     * @brief Adds removed files with version to map
     * @param list List of files in path
     * @param version Version where file was deleted
     */
    void addRemovedFiles( QStringList list, int version );

    void removeRemovedFiles( QString name );

    void printRemovedFiles();

private:
    /**
     * QList<Git::GitVersion*> versions
     * @brief List of versions
     */
    QList<Git::GitVersion*> versions;

    /**
     * QMap<QString, int> removedFiles
     * @brief Map of names of files which was deleted in Nth version
     */
    QMap<QString, int> removedFiles;

    /**
     * int lifespan
     * @brief Lifespan of deleted files in graph
     */
    int lifespan;

    /**
     * QString filePath
     * @brief Path to the git repository on file system
     */
    QString filePath;

}; // class
} // namespace
#endif // GITEVOLUTIONGRAPH_H
