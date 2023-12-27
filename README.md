# gembedded

The aim of project is :

1.  Applying modern Clean-Code and Design Patterns,
2.  Annotation based application development, Context and Dependency Injection,
3.  Inversion of Control,
4.  Executor services with worker classes. Like EJB vs.
5.  Remote access low level socket programming library like non-blocking io (selector) techniques. Very meaningful annotations like JAX-RS

Project is under development and supports only Raspbi-4B on Ubuntu.

You must run application with root privillage.

PLEASE DO NOT DOWNLOAD CODES FROM GITHUB. BECAUSE I ALWAYS MAKE CHANGES. INSTEAD YOU CAN USE REPOSITORY AND VERSIONS BELOW

Tutorial => https://github.com/cogo152/gembedded-tutorial

```
    repository :

    curl -s https://packagecloud.io/install/repositories/cogo152/gproject/script.deb.sh | sudo bash

    library dependency :

    sudo apt-get install gembedded-native

    pom.xml :

    <repositories>
        <repository>
            <id>cogo152-gproject</id>
            <url>https://packagecloud.io/cogo152/gproject/maven2</url>
            <releases>
                <enabled>true</enabled>
            </releases>
            <snapshots>
                <enabled>true</enabled>
            </snapshots>
        </repository>
    </repositories>

    <properties>
        <java.version>21</java.version>
        <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
        <maven.compiler.source>${java.version}</maven.compiler.source>
        <maven.compiler.target>${java.version}</maven.compiler.target>
        <gembedded.version>1.0.0-SNAPSHOT</gembedded.version>
    </properties>

     <dependencies>
        <dependency>
            <groupId>com.comert</groupId> <!--Mandatory, this is specification of the project-->
            <artifactId>gembedded-api</artifactId>
            <version>${gembedded.version}</version>
            <scope>compile</scope>
        </dependency>
        <dependency>
            <groupId>com.comert</groupId> <!--Mandatory, this is provider of the project, only one provider have to be selected-->
            <artifactId>gembedded-provider</artifactId>
            <version>${gembedded.version}</version>
            <scope>compile</scope>
        </dependency>
        <dependency>
            <groupId>com.comert</groupId> <!--Mandatory, this is native library interface of the project-->
            <artifactId>gembedded-native</artifactId>
            <version>${gembedded.version}</version>
            <scope>compile</scope>
        </dependency>
        <dependency>
            <groupId>com.comert</groupId> <!--Optional, this is component library of the project, like i2c components, gyros, servos etc.-->
            <artifactId>gembedded-component</artifactId>
            <version>${gembedded.version}</version>
            <scope>compile</scope>
        </dependency>
    </dependencies>   

```
