/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <QtSql/QtSql>

#include "../qsqldatabase/tst_databases.h"

const QString qtest(qTableName( "qtest", __FILE__ ));

//TESTED_FILES=

class tst_QSqlQuery : public QObject
{
    Q_OBJECT

public:
    tst_QSqlQuery();
    virtual ~tst_QSqlQuery();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void value_data() { generic_data(); }
    void value();
    void isValid_data() { generic_data(); }
    void isValid();
    void isActive_data() { generic_data(); }
    void isActive();
    void isSelect_data() { generic_data(); }
    void isSelect();
    void numRowsAffected_data() { generic_data(); }
    void numRowsAffected();
    void size_data() { generic_data(); }
    void size();
    void isNull_data() { generic_data(); }
    void isNull();
    void query_exec_data() { generic_data(); }
    void query_exec();
    void execErrorRecovery_data() { generic_data(); }
    void execErrorRecovery();
    void first_data() { generic_data(); }
    void first();
    void next_data() { generic_data(); }
    void next();
    void prev_data() { generic_data(); }
    void prev();
    void last_data() { generic_data(); }
    void last();
    void seek_data() { generic_data(); }
    void seek();
    void transaction_data() { generic_data(); }
    void transaction();
    void record_data() { generic_data(); }
    void record();
    void record_sqlite_data() { generic_data("QSQLITE"); }
    void record_sqlite();
    void finish_data() { generic_data(); }
    void finish();
    void sqlite_finish_data() { generic_data(); }
    void sqlite_finish();
    void nextResult_data() { generic_data(); }
    void nextResult();

    // forwardOnly mode need special treatment
    void forwardOnly_data() { generic_data(); }
    void forwardOnly();

    // bug specific tests
    void bitField_data() {generic_data("QTDS"); }
    void bitField();
    void nullBlob_data() { generic_data("QOCI"); }
    void nullBlob();
    void blob_data() { generic_data(); }
    void blob();
    void rawField_data() { generic_data("QOCI"); }
    void rawField();
    void precision_data() { generic_data(); }
    void precision();
    void nullResult_data() { generic_data(); }
    void nullResult();
    void joins_data() { generic_data(); }
    void joins();
    void outValues_data() { generic_data(); }
    void outValues();
    void char1Select_data() { generic_data(); }
    void char1Select();
    void char1SelectUnicode_data() { generic_data(); }
    void char1SelectUnicode();
    void synonyms_data() { generic_data(); }
    void synonyms();
    void oraOutValues_data() { generic_data("QOCI"); }
    void oraOutValues();
    void mysqlOutValues_data() { generic_data("QMYSQL"); }
    void mysqlOutValues();
    void oraClob_data() { generic_data("QOCI"); }
    void oraClob();
    void oraLong_data() { generic_data("QOCI"); }
    void oraLong();
    void oraOCINumber_data() { generic_data("QOCI"); }
    void oraOCINumber();
    void outValuesDB2_data() { generic_data("QDB2"); }
    void outValuesDB2();
    void storedProceduresIBase_data() {generic_data("QIBASE"); }
    void storedProceduresIBase();
    void oraRowId_data() { generic_data("QOCI"); }
    void oraRowId();
    void prepare_bind_exec_data() { generic_data(); }
    void prepare_bind_exec();
    void prepared_select_data() { generic_data(); }
    void prepared_select();
    void sqlServerLongStrings_data() { generic_data(); }
    void sqlServerLongStrings();
    void invalidQuery_data() { generic_data(); }
    void invalidQuery();
    void batchExec_data() { generic_data(); }
    void batchExec();
    void oraArrayBind_data() { generic_data(); }
    void oraArrayBind();
    void lastInsertId_data() { generic_data(); }
    void lastInsertId();
    void lastQuery_data() { generic_data(); }
    void lastQuery();
    void bindWithDoubleColonCastOperator_data() { generic_data(); }
    void bindWithDoubleColonCastOperator();
    void queryOnInvalidDatabase_data() { generic_data(); }
    void queryOnInvalidDatabase();
    void createQueryOnClosedDatabase_data() { generic_data(); }
    void createQueryOnClosedDatabase();
    void seekForwardOnlyQuery_data() { generic_data(); }
    void seekForwardOnlyQuery();
    void reExecutePreparedForwardOnlyQuery_data() { generic_data(); }
    void reExecutePreparedForwardOnlyQuery();
    void blobsPreparedQuery_data() { generic_data(); }
    void blobsPreparedQuery();
    void emptyTableNavigate_data() { generic_data(); }
    void emptyTableNavigate();

#ifdef NOT_READY_YET
    void task_229811();
    void task_229811_data() { generic_data(); }
    void task_234422_data() {  generic_data(); }
    void task_234422();
#endif
    void task_217003_data() { generic_data(); }
    void task_217003();

    void task_250026_data() { generic_data("QODBC"); }
    void task_250026();
    void task_205701_data() { generic_data("QMYSQL"); }
    void task_205701();

    void task_233829_data() { generic_data("QPSQL"); }
    void task_233829();

    void sqlServerReturn0_data() { generic_data(); }
    void sqlServerReturn0();

    void QTBUG_551_data() { generic_data("QOCI"); }
    void QTBUG_551();

    void QTBUG_5251_data() { generic_data("QPSQL"); }
    void QTBUG_5251();
    void QTBUG_6421_data() { generic_data("QOCI"); }
    void QTBUG_6421();
    void QTBUG_6618_data() { generic_data("QODBC"); }
    void QTBUG_6618();
    void QTBUG_6852_data() { generic_data("QMYSQL"); }
    void QTBUG_6852();
    void QTBUG_5765_data() { generic_data("QMYSQL"); }
    void QTBUG_5765();
    void QTBUG_14132_data() { generic_data("QOCI"); }
    void QTBUG_14132();

    void sqlite_constraint_data() { generic_data("QSQLITE"); }
    void sqlite_constraint();

#if 0
    void benchmark_data() { generic_data(); }
    void benchmark();
#endif

private:
    // returns all database connections
    void generic_data(const QString &engine=QString());
    void dropTestTables( QSqlDatabase db );
    void createTestTables( QSqlDatabase db );
    void populateTestTables( QSqlDatabase db );

    tst_Databases dbs;
};

tst_QSqlQuery::tst_QSqlQuery()
{
}

tst_QSqlQuery::~tst_QSqlQuery()
{
}

void tst_QSqlQuery::initTestCase()
{
    dbs.open();

    for ( QStringList::ConstIterator it = dbs.dbNames.begin(); it != dbs.dbNames.end(); ++it ) {
        QSqlDatabase db = QSqlDatabase::database(( *it ) );
        CHECK_DATABASE( db );
        dropTestTables( db ); //in case of leftovers
        createTestTables( db );
        populateTestTables( db );
    }
}

void tst_QSqlQuery::cleanupTestCase()
{
    for ( QStringList::ConstIterator it = dbs.dbNames.begin(); it != dbs.dbNames.end(); ++it ) {
        QSqlDatabase db = QSqlDatabase::database(( *it ) );
        CHECK_DATABASE( db );
        dropTestTables( db );
    }

    dbs.close();
}

void tst_QSqlQuery::init()
{
}

void tst_QSqlQuery::cleanup()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( QTest::currentTestFunction() == QLatin1String( "numRowsAffected" )
            || QTest::currentTestFunction() == QLatin1String( "transactions" )
            || QTest::currentTestFunction() == QLatin1String( "size" )
            || QTest::currentTestFunction() == QLatin1String( "isActive" )
            || QTest::currentTestFunction() == QLatin1String( "lastInsertId" ) ) {
        populateTestTables( db );
    }

    if ( QTest::currentTestFailed() && ( db.driverName().startsWith( "QOCI" )
                                         || db.driverName().startsWith( "QODBC" ) ) ) {
        //since Oracle ODBC totally craps out on error, we init again
        db.close();
        db.open();
    }
}

void tst_QSqlQuery::generic_data(const QString& engine)
{
    if ( dbs.fillTestTable(engine) == 0 ) {
        if(engine.isEmpty())
           QSKIP( "No database drivers are available in this Qt configuration", SkipAll );
        else
           QSKIP( (QString("No database drivers of type %1 are available in this Qt configuration").arg(engine)).toLocal8Bit(), SkipAll );
    }
}

void tst_QSqlQuery::dropTestTables( QSqlDatabase db )
{
    QStringList tablenames;
    // drop all the table in case a testcase failed
    tablenames <<  qtest
               << qTableName( "qtest_null", __FILE__ )
               << qTableName( "qtest_blob", __FILE__ )
               << qTableName( "qtest_bittest", __FILE__ )
               << qTableName( "qtest_nullblob", __FILE__ )
               << qTableName( "qtest_rawtest", __FILE__ )
               << qTableName( "qtest_precision", __FILE__ )
               << qTableName( "qtest_prepare", __FILE__ )
               << qTableName( "qtestj1", __FILE__ )
               << qTableName( "qtestj2", __FILE__ )
               << qTableName( "char1Select", __FILE__ )
               << qTableName( "char1SU", __FILE__ )
               << qTableName( "qxmltest", __FILE__ )
               << qTableName( "qtest_exerr", __FILE__ )
               << qTableName( "qtest_empty", __FILE__ )
               << qTableName( "clobby", __FILE__ )
               << qTableName( "bindtest", __FILE__ )
               << qTableName( "more_results", __FILE__ )
               << qTableName( "blobstest", __FILE__ )
               << qTableName( "oraRowId", __FILE__ )
               << qTableName( "qtest_batch", __FILE__ )
               << qTableName("bug6421", __FILE__).toUpper()
               << qTableName("bug5765", __FILE__)
               << qTableName("bug6852", __FILE__)
               << qTableName( "qtest_lockedtable", __FILE__ )
               << qTableName( "Planet", __FILE__ )
               << qTableName( "task_250026", __FILE__ )
               << qTableName( "task_234422", __FILE__ )
               << qTableName("test141895", __FILE__)
               << qTableName("qtest_oraOCINumber", __FILE__);

    if ( db.driverName().startsWith("QPSQL") )
        tablenames << qTableName("task_233829", __FILE__);

    if ( db.driverName().startsWith("QSQLITE") )
        tablenames << qTableName( "record_sqlite", __FILE__ );

    if ( tst_Databases::isSqlServer( db ) || db.driverName().startsWith( "QOCI" ) )
        tablenames << qTableName( "qtest_longstr", __FILE__ );

    if (tst_Databases::isSqlServer( db ))
        db.exec("DROP PROCEDURE " + qTableName("test141895_proc", __FILE__));

    if (tst_Databases::isMySQL( db ))
        db.exec("DROP PROCEDURE IF EXISTS "+qTableName("bug6852_proc", __FILE__));

    tst_Databases::safeDropTables( db, tablenames );

    if ( db.driverName().startsWith( "QOCI" ) ) {
        QSqlQuery q( db );
        q.exec( "DROP PACKAGE " + qTableName("pkg", __FILE__) );
    }
}

void tst_QSqlQuery::createTestTables( QSqlDatabase db )
{
    QSqlQuery q( db );

    if ( db.driverName().startsWith( "QMYSQL" ) )
        // ### stupid workaround until we find a way to hardcode this
        // in the MySQL server startup script
        q.exec( "set table_type=innodb" );
    else if(tst_Databases::isPostgreSQL(db))
        QVERIFY_SQL( q, exec("set client_min_messages='warning'"));

    if(tst_Databases::isPostgreSQL(db))
        QVERIFY_SQL( q, exec( "create table " + qtest + " (id serial NOT NULL, t_varchar varchar(20), t_char char(20), primary key(id)) WITH OIDS" ) );
    else
        QVERIFY_SQL( q, exec( "create table " + qtest + " (id int "+tst_Databases::autoFieldName(db) +" NOT NULL, t_varchar varchar(20), t_char char(20), primary key(id))" ) );

    if ( tst_Databases::isSqlServer( db ) || db.driverName().startsWith( "QTDS" ) )
        QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_null", __FILE__ ) + " (id int null, t_varchar varchar(20) null)" ) );
    else
        QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_null", __FILE__ ) + " (id int, t_varchar varchar(20))" ) );
}

void tst_QSqlQuery::populateTestTables( QSqlDatabase db )
{
    QSqlQuery q( db );
    const QString qtest_null(qTableName( "qtest_null", __FILE__ ));
    q.exec( "delete from " + qtest );
    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (1, 'VarChar1', 'Char1')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (2, 'VarChar2', 'Char2')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (3, 'VarChar3', 'Char3')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (4, 'VarChar4', 'Char4')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (5, 'VarChar5', 'Char5')" ) );

    q.exec( "delete from " + qtest_null );
    QVERIFY_SQL( q, exec( "insert into " + qtest_null + " values (0, NULL)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_null + " values (1, 'n')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_null + " values (2, 'i')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_null + " values (3, NULL)" ) );
}

// There were problems with char fields of size 1
void tst_QSqlQuery::char1Select()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    {
        QSqlQuery q( db );
        QVERIFY_SQL( q, exec( "create table " + qTableName( "char1Select", __FILE__ ) + " (id char(1))" ) );
        QVERIFY_SQL( q, exec( "insert into " + qTableName( "char1Select", __FILE__ ) + " values ('a')" ) );
        QVERIFY_SQL( q, exec( "select * from " + qTableName( "char1Select", __FILE__ ) ) );
        QVERIFY( q.next() );

        if ( db.driverName().startsWith( "QIBASE" ) )
            QCOMPARE( q.value( 0 ).toString().left( 1 ), QString( "a" ) );
        else
            QCOMPARE( q.value( 0 ).toString(), QString( "a" ) );

        QVERIFY( !q.next() );
    }
}

void tst_QSqlQuery::char1SelectUnicode()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if(db.driverName().startsWith("QDB2"))
        QSKIP("Needs someone with more Unicode knowledge than I have to fix", SkipSingle);

    if ( db.driver()->hasFeature( QSqlDriver::Unicode ) ) {
        QString uniStr( QChar(0x0915) ); // DEVANAGARI LETTER KA
        QSqlQuery q( db );

        if ( db.driverName().startsWith( "QMYSQL" ) && tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
            QSKIP( "Test requires MySQL >= 5.0", SkipSingle );

        QString createQuery;
        const QString char1SelectUnicode(qTableName( "char1SU", __FILE__ ));

        if ( tst_Databases::isSqlServer( db ) )
            createQuery = "create table " + char1SelectUnicode + "(id nchar(1))";
        else if ( db.driverName().startsWith( "QDB2" )
                  || db.driverName().startsWith( "QOCI" )
                  || db.driverName().startsWith( "QPSQL" ) )
            createQuery = "create table " + char1SelectUnicode + " (id char(3))";
        else if ( db.driverName().startsWith( "QIBASE" ) )
            createQuery = "create table " + char1SelectUnicode +
                          " (id char(1) character set unicode_fss)";
        else if ( db.driverName().startsWith( "QMYSQL" ) )
            createQuery = "create table " + char1SelectUnicode + " (id char(1)) "
                          "default character set 'utf8'";
        else
            createQuery = "create table " + char1SelectUnicode + " (id char(1))";

        QVERIFY_SQL( q, exec( createQuery ) );

        QVERIFY_SQL( q, prepare( "insert into " + char1SelectUnicode + " values(?)" ) );

        q.bindValue( 0, uniStr );

        QVERIFY_SQL( q, exec() );

        QVERIFY_SQL( q, exec( "select * from " + char1SelectUnicode ) );

        QVERIFY( q.next() );

        if ( !q.value( 0 ).toString().isEmpty() )
            QCOMPARE( q.value( 0 ).toString()[ 0 ].unicode(), uniStr[0].unicode() );

        QCOMPARE( q.value( 0 ).toString().trimmed(), uniStr );

        QVERIFY( !q.next() );
    }
    else
        QSKIP( "Database not unicode capable", SkipSingle );
}

void tst_QSqlQuery::oraRowId()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString oraRowId(qTableName("oraRowId", __FILE__));

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "select rowid from " + qtest ) );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).type(), QVariant::String );
    QVERIFY( !q.value( 0 ).toString().isEmpty() );

    QVERIFY_SQL( q, exec( "create table " + oraRowId + " (id char(1))" ) );

    QVERIFY_SQL( q, exec( "insert into " + oraRowId + " values('a')" ) );
    QVariant v1 = q.lastInsertId();
    QVERIFY( v1.isValid() );

    QVERIFY_SQL( q, exec( "insert into " + oraRowId + " values('b')" ) );
    QVariant v2 = q.lastInsertId();
    QVERIFY( v2.isValid() );

    QVERIFY_SQL( q, prepare( "select * from " + oraRowId + " where rowid = ?" ) );
    q.addBindValue( v1 );
    QVERIFY_SQL( q, exec() );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toString(), QString( "a" ) );

    q.addBindValue( v2 );
    QVERIFY_SQL( q, exec() );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toString(), QString( "b" ) );
}

void tst_QSqlQuery::mysqlOutValues()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString hello(qTableName( "hello", __FILE__ )), qtestproc(qTableName( "qtestproc", __FILE__ ));

    QSqlQuery q( db );

    if ( db.driverName().startsWith( "QMYSQL" ) && tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
        QSKIP( "Test requires MySQL >= 5.0", SkipSingle );

    q.exec( "drop function " + hello );

    QVERIFY_SQL( q, exec( "create function " + hello + " (s char(20)) returns varchar(50) return concat('Hello ', s)" ) );

    QVERIFY_SQL( q, exec( "select " + hello + "('world')" ) );
    QVERIFY_SQL( q, next() );

    QCOMPARE( q.value( 0 ).toString(), QString( "Hello world" ) );

    QVERIFY_SQL( q, prepare( "select " + hello + "('harald')" ) );
    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, next() );

    QCOMPARE( q.value( 0 ).toString(), QString( "Hello harald" ) );

    QVERIFY_SQL( q, exec( "drop function " + hello ) );

    q.exec( "drop procedure " + qtestproc );

    QVERIFY_SQL( q, exec( "create procedure " + qtestproc + " () "
                            "BEGIN select * from " + qtest + " order by id; END" ) );
    QVERIFY_SQL( q, exec( "call " + qtestproc + "()" ) );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 1 ).toString(), QString( "VarChar1" ) );

    QVERIFY_SQL( q, exec( "drop procedure " + qtestproc ) );

    QVERIFY_SQL( q, exec( "create procedure " + qtestproc + " (OUT param1 INT) "
                            "BEGIN set param1 = 42; END" ) );

    QVERIFY_SQL( q, exec( "call " + qtestproc + " (@out)" ) );
    QVERIFY_SQL( q, exec( "select @out" ) );
    QCOMPARE( q.record().fieldName( 0 ), QString( "@out" ) );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), 42 );

    QVERIFY_SQL( q, exec( "drop procedure " + qtestproc ) );
}

void tst_QSqlQuery::oraOutValues()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString tst_outValues(qTableName("tst_outValues", __FILE__));

    if ( !db.driver()->hasFeature( QSqlDriver::PreparedQueries ) ) {
        QSKIP( "Test requires prepared query support", SkipSingle );
        return;
    }

    QSqlQuery q( db );

    q.setForwardOnly( true );

    /*** outvalue int ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x out int) is\n"
                            "begin\n"
                            "    x := 42;\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    q.addBindValue( 0, QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 0 ).toInt(), 42 );

    // bind a null value, make sure the OCI driver resets the null flag
    q.addBindValue( QVariant( QVariant::Int ), QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 0 ).toInt(), 42 );
    QVERIFY( !q.boundValue( 0 ).isNull() );

    /*** outvalue varchar ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x out varchar) is\n"
                            "begin\n"
                            "    x := 'blah';\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    QString s1( "12345" );
    s1.reserve( 512 );
    q.addBindValue( s1, QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 0 ).toString(), QString( "blah" ) );

    /*** in/outvalue numeric ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x in out numeric) is\n"
                            "begin\n"
                            "    x := x + 10;\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    q.addBindValue( 10, QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 0 ).toInt(), 20 );

    /*** in/outvalue varchar ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x in out varchar) is\n"
                            "begin\n"
                            "    x := 'homer';\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    q.addBindValue( QString( "maggy" ), QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 0 ).toString(), QString( "homer" ) );

    /*** in/outvalue varchar ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x in out varchar) is\n"
                            "begin\n"
                            "    x := NULL;\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    q.addBindValue( QString( "maggy" ), QSql::Out );
    QVERIFY_SQL( q, exec() );
    QVERIFY( q.boundValue( 0 ).isNull() );

    /*** in/outvalue int ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x in out int) is\n"
                            "begin\n"
                            "    x := NULL;\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    q.addBindValue( 42, QSql::Out );
    QVERIFY_SQL( q, exec() );
    QVERIFY( q.boundValue( 0 ).isNull() );

    /*** in/outvalue varchar ***/
    QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x in varchar, y out varchar) is\n"
                            "begin\n"
                            "    y := x||'bubulalakikikokololo';\n"
                            "end;\n" ) );
    QVERIFY( q.prepare( "call " + tst_outValues + "(?, ?)" ) );
    q.addBindValue( QString( "fifi" ), QSql::In );
    QString out;
    out.reserve( 50 );
    q.addBindValue( out, QSql::Out );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.boundValue( 1 ).toString(), QString( "fifibubulalakikikokololo" ) );
}

void tst_QSqlQuery::oraClob()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString clobby(qTableName("clobby", __FILE__));

    QSqlQuery q( db );

    // simple short string
    QVERIFY_SQL( q, exec( "create table " + clobby + "(id int primary key, cl clob, bl blob)" ) );
    QVERIFY_SQL( q, prepare( "insert into " + clobby + " (id, cl, bl) values(?, ?, ?)" ) );
    q.addBindValue( 1 );
    q.addBindValue( "bubu" );
    q.addBindValue( QByteArray("bubu") );
    QVERIFY_SQL( q, exec() );

    QVERIFY_SQL( q, exec( "select bl, cl from " + clobby + " where id = 1" ) );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toString(), QString( "bubu" ) );
    QCOMPARE( q.value( 1 ).toString(), QString( "bubu" ) );

    // simple short string with binding
    QVERIFY_SQL( q, prepare( "insert into " + clobby + " (id, cl, bl) values(?, ?, ?)" ) );
    q.addBindValue( 2 );
    q.addBindValue( "lala", QSql::Binary );
    q.addBindValue( QByteArray("lala"), QSql::Binary );
    QVERIFY_SQL( q, exec() );

    QVERIFY_SQL( q, exec( "select bl, cl from " + clobby + " where id = 2" ) );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toString(), QString( "lala" ) );
    QCOMPARE( q.value( 1 ).toString(), QString( "lala" ) );

    // loooong string
    QString loong;
    loong.fill( QLatin1Char( 'A' ), 25000 );
    QVERIFY_SQL( q, prepare( "insert into " + clobby + " (id, cl, bl) values(?, ?, ?)" ) );
    q.addBindValue( 3 );
    q.addBindValue( loong, QSql::Binary );
    q.addBindValue( loong.toLatin1(), QSql::Binary );
    QVERIFY_SQL( q, exec() );

    QVERIFY_SQL( q, exec( "select bl, cl from " + clobby + " where id = 3" ) );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toString().count(), loong.count() );
    QVERIFY( q.value( 0 ).toString() == loong );
    QCOMPARE( q.value( 1 ).toByteArray().count(), loong.toLatin1().count() );
    QVERIFY( q.value( 1 ).toByteArray() == loong.toLatin1() );
}

void tst_QSqlQuery::storedProceduresIBase()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    q.exec( "drop procedure " + qTableName( "TESTPROC", __FILE__ ) );

    QVERIFY_SQL( q, exec( "create procedure " + qTableName( "TESTPROC", __FILE__ ) +
                            " RETURNS (x integer, y varchar(20)) "
                            "AS BEGIN "
                            "  x = 42; "
                            "  y = 'Hello Anders'; "
                            "END" ) );

    QVERIFY_SQL( q, prepare( "execute procedure " + qTableName( "TestProc", __FILE__ ) ) );
    QVERIFY_SQL( q, exec() );

    // check for a valid result set
    QSqlRecord rec = q.record();
    QCOMPARE( rec.count(), 2 );
    QCOMPARE( rec.fieldName( 0 ).toUpper(), QString( "X" ) );
    QCOMPARE( rec.fieldName( 1 ).toUpper(), QString( "Y" ) );

    // the first next shall suceed
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), 42 );
    QCOMPARE( q.value( 1 ).toString(), QString( "Hello Anders" ) );

    // the second next shall fail
    QVERIFY( !q.next() );

    q.exec( "drop procedure " + qTableName( "TestProc", __FILE__ ) );
}

void tst_QSqlQuery::outValuesDB2()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::PreparedQueries ) ) {
        QSKIP( "Test requires prepared query support", SkipSingle );
        return;
    }

    QSqlQuery q( db );

    q.setForwardOnly( true );

    q.exec( "drop procedure " + qTableName( "tst_outValues", __FILE__ ) ); //non-fatal
    QVERIFY_SQL( q, exec( "CREATE PROCEDURE " + qTableName( "tst_outValues", __FILE__ ) +
                            " (OUT x int, OUT x2 double, OUT x3 char(20))\n"
                            "LANGUAGE SQL\n"
                            "P1: BEGIN\n"
                            " SET x = 42;\n"
                            " SET x2 = 4.2;\n"
                            " SET x3 = 'Homer';\n"
                            "END P1" ) );

    QVERIFY_SQL( q, prepare( "call " + qTableName( "tst_outValues", __FILE__ ) + "(?, ?, ?)" ) );

    q.addBindValue( 0, QSql::Out );
    q.addBindValue( 0.0, QSql::Out );
    q.addBindValue( "Simpson", QSql::Out );

    QVERIFY_SQL( q, exec() );

    QCOMPARE( q.boundValue( 0 ).toInt(), 42 );
    QCOMPARE( q.boundValue( 1 ).toDouble(), 4.2 );
    QCOMPARE( q.boundValue( 2 ).toString().trimmed(), QString( "Homer" ) );
}

void tst_QSqlQuery::outValues()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString tst_outValues(qTableName("tst_outValues", __FILE__));

    if ( !db.driver()->hasFeature( QSqlDriver::PreparedQueries ) ) {
        QSKIP( "Test requires prepared query support", SkipSingle );
        return;
    }

    QSqlQuery q( db );

    q.setForwardOnly( true );

    if ( db.driverName().startsWith( "QOCI" ) ) {
        QVERIFY_SQL( q, exec( "create or replace procedure " + tst_outValues + "(x out int) is\n"
                                "begin\n"
                                "    x := 42;\n"
                                "end;\n" ) );
        QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    } else if ( db.driverName().startsWith( "QDB2" ) ) {
        q.exec( "drop procedure " + tst_outValues ); //non-fatal
        QVERIFY_SQL( q, exec( "CREATE PROCEDURE " + tst_outValues + " (OUT x int)\n"
                                "LANGUAGE SQL\n"
                                "P1: BEGIN\n"
                                " SET x = 42;\n"
                                "END P1" ) );
        QVERIFY( q.prepare( "call " + tst_outValues + "(?)" ) );
    } else if ( tst_Databases::isSqlServer( db ) ) {
        q.exec( "drop procedure " + tst_outValues );  //non-fatal
        QVERIFY_SQL( q, exec( "create procedure " + tst_outValues + " (@x int out) as\n"
                                "begin\n"
                                "    set @x = 42\n"
                                "end\n" ) );
        QVERIFY( q.prepare( "{call " + tst_outValues + "(?)}" ) );
    } else {
        QSKIP( "Don't know how to create a stored procedure for this database server, please fix this test", SkipSingle );
        return;
    }

    q.addBindValue( 0, QSql::Out );

    QVERIFY_SQL( q, exec() );

    QCOMPARE( q.boundValue( 0 ).toInt(), 42 );
}

void tst_QSqlQuery::blob()
{
    static const int BLOBSIZE = 1024 * 10;
    static const int BLOBCOUNT = 2;

    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::BLOB ) )
        QSKIP( "DBMS not BLOB capable", SkipSingle );

    //don' make it too big otherwise sybase and mysql will complain
    QByteArray ba( BLOBSIZE, 0 );

    int i;

    for ( i = 0; i < ( int )ba.size(); ++i )
        ba[i] = i % 256;

    QSqlQuery q( db );

    q.setForwardOnly( true );

    QString queryString = QString( "create table " + qTableName( "qtest_blob", __FILE__ ) +
                                   " (id int not null primary key, t_blob %1)" ).arg( tst_Databases::blobTypeName( db, BLOBSIZE ) );
    QVERIFY_SQL( q, exec( queryString ) );

    QVERIFY_SQL( q, prepare( "insert into " + qTableName( "qtest_blob", __FILE__ ) + " (id, t_blob) values (?, ?)" ) );

    for ( i = 0; i < BLOBCOUNT; ++i ) {
        q.addBindValue( i );
        q.addBindValue( ba );
        QVERIFY_SQL( q, exec() );
    }

    QVERIFY_SQL( q, exec( "select * from " + qTableName( "qtest_blob", __FILE__ ) ) );

    for ( i = 0; i < BLOBCOUNT; ++i ) {
        QVERIFY( q.next() );
        QByteArray res = q.value( 1 ).toByteArray();
        QVERIFY2( res.size() >= ba.size(),
                  QString( "array sizes differ, expected %1, got %2" ).arg( ba.size() ).arg( res.size() ).toLatin1() );

        for ( int i2 = 0; i2 < ( int )ba.size(); ++i2 ) {
            if ( res[i2] != ba[i2] )
                QFAIL( QString( "ByteArrays differ at position %1, expected %2, got %3" ).arg(
                           i2 ).arg(( int )( unsigned char )ba[i2] ).arg(( int )( unsigned char )res[i2] ).toLatin1() );
        }
    }
}

void tst_QSqlQuery::value()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "select id, t_varchar, t_char from " + qtest + " order by id" ) );
    int i = 1;

    while ( q.next() ) {
        QCOMPARE( q.value( 0 ).toInt(), i );

        if ( db.driverName().startsWith( "QIBASE" ) )
            QVERIFY( q.value( 1 ).toString().startsWith( "VarChar" + QString::number( i ) ) );
        else if ( q.value( 1 ).toString().right( 1 ) == " " )
            QCOMPARE( q.value( 1 ).toString(), ( "VarChar" + QString::number( i ) + "            " ) );
        else
            QCOMPARE( q.value( 1 ).toString(), ( "VarChar" + QString::number( i ) ) );

        if ( db.driverName().startsWith( "QIBASE" ) )
            QVERIFY( q.value( 2 ).toString().startsWith( "Char" + QString::number( i ) ) );
        else if ( q.value( 2 ).toString().right( 1 ) != " " )
            QCOMPARE( q.value( 2 ).toString(), ( "Char" + QString::number( i ) ) );
        else
            QCOMPARE( q.value( 2 ).toString(), ( "Char" + QString::number( i ) + "               " ) );

        i++;
    }
}

void tst_QSqlQuery::record()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( q.record().isEmpty() );
    QVERIFY_SQL( q, exec( "select id, t_varchar, t_char from " + qtest + " order by id" ) );
    QSqlRecord rec = q.record();
    QCOMPARE( q.record().fieldName( 0 ).toLower(), QString( "id" ) );
    QCOMPARE( q.record().fieldName( 1 ).toLower(), QString( "t_varchar" ) );
    QCOMPARE( q.record().fieldName( 2 ).toLower(), QString( "t_char" ) );
    QVERIFY( !q.record().value( 0 ).isValid() );
    QVERIFY( !q.record().value( 1 ).isValid() );
    QVERIFY( !q.record().value( 2 ).isValid() );

    QVERIFY( q.next() );
    QVERIFY( q.next() );

    QCOMPARE( q.record().fieldName( 0 ).toLower(), QString( "id" ) );
    QCOMPARE( q.value( 0 ).toInt(), 2 );
}

void tst_QSqlQuery::isValid()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( !q.isValid() );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.first() );
    QVERIFY( q.isValid() );
}

void tst_QSqlQuery::isActive()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( !q.isActive() );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.isActive() );
    QVERIFY( q.last() );

    if ( !tst_Databases::isMSAccess( db ) )
        // Access is stupid enough to let you scroll over boundaries
        QVERIFY( !q.next() );

    QVERIFY( q.isActive() );

    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (41, 'VarChar41', 'Char41')" ) );

    QVERIFY( q.isActive() );

    QVERIFY_SQL( q, exec( "update " + qtest + " set id = 42 where id = 41" ) );

    QVERIFY( q.isActive() );

    QVERIFY_SQL( q, exec( "delete from " + qtest + " where id = 42" ) );

    QVERIFY( q.isActive() );
}

void tst_QSqlQuery::numRowsAffected()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QCOMPARE( q.numRowsAffected(), -1 );

    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    int i = 0;

    while ( q.next() )
        ++i;

    if ( q.numRowsAffected() == -1 || q.numRowsAffected() == 0 )
        QSKIP("Database doesn't support numRowsAffected", SkipSingle);

    if ( q.numRowsAffected() != -1 && q.numRowsAffected() != 0 && q.numRowsAffected() != i ) {
        // the value is undefined for SELECT, this check is just here for curiosity
        qDebug( "Expected numRowsAffected to be -1, 0 or %d, got %d", i, q.numRowsAffected() );
    }

    QVERIFY_SQL( q, exec( "update " + qtest + " set id = 100 where id = 1" ) );

    QCOMPARE( q.numRowsAffected(), 1 );
    QCOMPARE( q.numRowsAffected(), 1 ); // yes, we check twice

    QVERIFY_SQL( q, exec( "update " + qtest + " set id = id + 100" ) );
    QCOMPARE( q.numRowsAffected(), i );
    QCOMPARE( q.numRowsAffected(), i ); // yes, we check twice

    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (42000, 'homer', 'marge')" ) );
    QCOMPARE( q.numRowsAffected(), 1 );
    QCOMPARE( q.numRowsAffected(), 1 ); // yes, we check twice

    QSqlQuery q2( db );
    QVERIFY_SQL( q2, exec( "insert into " + qtest + " values (42001, 'homer', 'marge')" ) );

    if ( !db.driverName().startsWith( "QSQLITE2" ) ) {
        // SQLite 2.x accumulates changed rows in nested queries. See task 33794
        QCOMPARE( q2.numRowsAffected(), 1 );
        QCOMPARE( q2.numRowsAffected(), 1 ); // yes, we check twice
    }
}

void tst_QSqlQuery::size()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QCOMPARE( q.size(), -1 );

    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    int i = 0;

    while ( q.next() )
        ++i;

    if ( db.driver()->hasFeature( QSqlDriver::QuerySize ) ) {
        QCOMPARE( q.size(), i );
        QCOMPARE( q.size(), i ); // yes, twice
    } else {
        QCOMPARE( q.size(), -1 );
        QCOMPARE( q.size(), -1 ); // yes, twice
    }

    QSqlQuery q2( "select * from " + qtest, db );

    if ( db.driver()->hasFeature( QSqlDriver::QuerySize ) )
        QCOMPARE( q.size(), i );
    else
        QCOMPARE( q.size(), -1 );

    q2.clear();

    QVERIFY_SQL( q, exec( "update " + qtest + " set id = 100 where id = 1" ) );
    QCOMPARE( q.size(), -1 );
    QCOMPARE( q.size(), -1 ); // yes, twice
}

void tst_QSqlQuery::isSelect()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.isSelect() );

    QVERIFY_SQL( q, exec( "update " + qtest + " set id = 1 where id = 1" ) );
    QVERIFY( q.isSelect() == false );
}

void tst_QSqlQuery::first()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.last() );
    QVERIFY_SQL( q, first() );
    QVERIFY( q.at() == 0 );
}

void tst_QSqlQuery::next()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.first() );
    QVERIFY( q.next() );
    QVERIFY( q.at() == 1 );
}

void tst_QSqlQuery::prev()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.first() );
    QVERIFY( q.next() );
    QVERIFY( q.previous() );
    QVERIFY( q.at() == 0 );
}

void tst_QSqlQuery::last()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QCOMPARE( q.at(), int( QSql::BeforeFirstRow ) );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    int i = 0;

    while ( q.next() )
        i++;

    QCOMPARE( q.at(), int( QSql::AfterLastRow ) );

    QVERIFY( q.last() );

    QSet<int> validReturns(QSet<int>() << -1 << i-1);
    QVERIFY( validReturns.contains(q.at()) );

    QSqlQuery q2( "select * from " + qtest, db );

    QVERIFY( q2.last() );

    QVERIFY( validReturns.contains(q.at()) );
}

void tst_QSqlQuery::seek()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    QSqlQuery q( db );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( QString( "select id from %1 order by id" ).arg( qtest ) ) );

    // NB! The order of the calls below are important!
    QVERIFY( q.last() );
    QVERIFY( !q.seek( QSql::BeforeFirstRow ) );
    QCOMPARE( q.at(), int( QSql::BeforeFirstRow ) );
    QVERIFY( q.seek( 0 ) );
    QCOMPARE( q.at(), 0 );
    QCOMPARE( q.value( 0 ).toInt(), 1 );

    QVERIFY( q.seek( 1 ) );
    QCOMPARE( q.at(), 1 );
    QCOMPARE( q.value( 0 ).toInt(), 2 );

    QVERIFY( q.seek( 3 ) );
    QCOMPARE( q.at(), 3 );
    QCOMPARE( q.value( 0 ).toInt(), 4 );

    QVERIFY( q.seek( -2, true ) );
    QCOMPARE( q.at(), 1 );
    QVERIFY( q.seek( 0 ) );
    QCOMPARE( q.at(), 0 );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
}

void tst_QSqlQuery::seekForwardOnlyQuery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    q.setForwardOnly( false );
    QVERIFY( !q.isForwardOnly() );

    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( QString( "select id from %1 order by id" ).arg( qtest ) ) );

    QSqlRecord rec;

    // NB! The order of the calls below are important!
    QVERIFY( q.seek( 0 ) );
    QCOMPARE( q.at(), 0 );
    rec = q.record();
    QCOMPARE( rec.value( 0 ).toInt(), 1 );

    QVERIFY( q.seek( 1 ) );
    QCOMPARE( q.at(), 1 );
    rec = q.record();
    QCOMPARE( rec.value( 0 ).toInt(), 2 );

    // Make a jump!
    QVERIFY( q.seek( 3 ) );
    QCOMPARE( q.at(), 3 );
    rec = q.record();
    QCOMPARE( rec.value( 0 ).toInt(), 4 );

    // Last record in result set
    QVERIFY( q.seek( 4 ) );
    QCOMPARE( q.at(), 4 );
    rec = q.record();
    QCOMPARE( rec.value( 0 ).toInt(), 5 );
}

// tests the forward only mode;
void tst_QSqlQuery::forwardOnly()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    q.setForwardOnly( true );
    QVERIFY( q.isForwardOnly() );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY_SQL( q, exec( "select * from " + qtest + " order by id" ) );
    QVERIFY( q.at() == QSql::BeforeFirstRow );
    QVERIFY( q.first() );
    QCOMPARE( q.at(), 0 );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QVERIFY( q.next() );
    QCOMPARE( q.at(), 1 );
    QCOMPARE( q.value( 0 ).toInt(), 2 );
    QVERIFY( q.next() );
    QCOMPARE( q.at(), 2 );
    QCOMPARE( q.value( 0 ).toInt(), 3 );

    // lets make some mistakes to see how robust it is
    QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::seek: cannot seek backwards in a forward only query" );
    QVERIFY( q.first() == false );
    QCOMPARE( q.at(), 2 );
    QCOMPARE( q.value( 0 ).toInt(), 3 );
    QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::seek: cannot seek backwards in a forward only query" );
    QVERIFY( q.previous() == false );
    QCOMPARE( q.at(), 2 );
    QCOMPARE( q.value( 0 ).toInt(), 3 );
    QVERIFY( q.next() );
    QCOMPARE( q.at(), 3 );
    QCOMPARE( q.value( 0 ).toInt(), 4 );

    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    int i = 0;

    while ( q.next() )
        i++;

    QVERIFY( q.at() == QSql::AfterLastRow );

    QSqlQuery q2 = q;

    QVERIFY( q2.isForwardOnly() );

    QVERIFY_SQL( q, exec( "select * from " + qtest + " order by id" ) );

    QVERIFY( q.isForwardOnly() );

    QVERIFY( q2.isForwardOnly() );

    QCOMPARE( q.at(), int( QSql::BeforeFirstRow ) );

    QVERIFY_SQL( q, seek( 3 ) );

    QCOMPARE( q.at(), 3 );

    QCOMPARE( q.value( 0 ).toInt(), 4 );

    QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::seek: cannot seek backwards in a forward only query" );

    QVERIFY( q.seek( 0 ) == false );

    QCOMPARE( q.value( 0 ).toInt(), 4 );

    QCOMPARE( q.at(), 3 );

    QVERIFY( q.last() );

    QCOMPARE( q.at(), i-1 );

    QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::seek: cannot seek backwards in a forward only query" );

    QVERIFY( q.first() == false );

    QCOMPARE( q.at(), i-1 );

    QVERIFY( q.next() == false );

    QCOMPARE( q.at(), int( QSql::AfterLastRow ) );
}

void tst_QSqlQuery::query_exec()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY( !q.isValid() );
    QVERIFY( !q.isActive() );
    QVERIFY_SQL( q, exec( "select * from " + qtest ) );
    QVERIFY( q.isActive() );
    QVERIFY( q.next() );
    QVERIFY( q.isValid() );
}

void tst_QSqlQuery::isNull()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "select id, t_varchar from " + qTableName( "qtest_null", __FILE__ ) + " order by id" ) );
    QVERIFY( q.next() );
    QVERIFY( !q.isNull( 0 ) );
    QVERIFY( q.isNull( 1 ) );
    QCOMPARE( q.value( 0 ).toInt(), 0 );
    QCOMPARE( q.value( 1 ).toString(), QString() );
    QVERIFY( !q.value( 0 ).isNull() );
    QVERIFY( q.value( 1 ).isNull() );

    QVERIFY( q.next() );
    QVERIFY( !q.isNull( 0 ) );
    QVERIFY( !q.isNull( 1 ) );
}

/*! TDS specific BIT field test */
void tst_QSqlQuery::bitField()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driverName().startsWith( "QTDS" ) )
        QSKIP( "TDS specific test", SkipSingle );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_bittest", __FILE__ ) + " (bitty bit)" ) );

    QVERIFY_SQL( q, exec( "insert into " + qTableName( "qtest_bittest", __FILE__ ) + " values (0)" ) );

    QVERIFY_SQL( q, exec( "insert into " + qTableName( "qtest_bittest", __FILE__ ) + " values (1)" ) );

    QVERIFY_SQL( q, exec( "select bitty from " + qTableName( "qtest_bittest", __FILE__ ) ) );

    QVERIFY( q.next() );

    QVERIFY( q.value( 0 ).toInt() == 0 );

    QVERIFY( q.next() );

    QVERIFY( q.value( 0 ).toInt() == 1 );
}


/*! Oracle specific NULL BLOB test */
void tst_QSqlQuery::nullBlob()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtest_nullblob(qTableName("qtest_nullblob", __FILE__));

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "create table " + qtest_nullblob + " (id int primary key, bb blob)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_nullblob + " values (0, EMPTY_BLOB())" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_nullblob + " values (1, NULL)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_nullblob + " values (2, 'aabbcc00112233445566')" ) );
    // necessary otherwise oracle will bombard you with internal errors
    q.setForwardOnly( true );
    QVERIFY_SQL( q, exec( "select * from " + qtest_nullblob + " order by id" ) );

    QVERIFY( q.next() );
    QCOMPARE(( int )q.value( 1 ).toByteArray().size(), 0 );
    QVERIFY( !q.isNull( 1 ) );

    QVERIFY( q.next() );
    QCOMPARE(( int )q.value( 1 ).toByteArray().size(), 0 );
    QVERIFY( q.isNull( 1 ) );

    QVERIFY( q.next() );
    QCOMPARE(( int )q.value( 1 ).toByteArray().size(), 10 );
    QVERIFY( !q.isNull( 1 ) );
}

/* Oracle specific RAW field test */
void tst_QSqlQuery::rawField()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtest_rawtest(qTableName("qtest_rawtest", __FILE__));

    QSqlQuery q( db );
    q.setForwardOnly( true );
    QVERIFY_SQL( q, exec( "create table " + qtest_rawtest +
                            " (id int, col raw(20))" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_rawtest + " values (0, NULL)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtest_rawtest + " values (1, '00aa1100ddeeff')" ) );
    QVERIFY_SQL( q, exec( "select col from " + qtest_rawtest + " order by id" ) );
    QVERIFY( q.next() );
    QVERIFY( q.isNull( 0 ) );
    QCOMPARE(( int )q.value( 0 ).toByteArray().size(), 0 );
    QVERIFY( q.next() );
    QVERIFY( !q.isNull( 0 ) );
    QCOMPARE(( int )q.value( 0 ).toByteArray().size(), 7 );
}

// test whether we can fetch values with more than DOUBLE precision
// note that MySQL's 3.x highest precision is that of a double, although
// you can define field with higher precision
void tst_QSqlQuery::precision()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtest_precision(qTableName( "qtest_precision", __FILE__ ));

    static const char* precStr = "1.2345678901234567891";

    if ( db.driverName().startsWith( "QIBASE" ) )
        QSKIP( "DB unable to store high precision", SkipSingle );

    {
        // need a new scope for SQLITE
        QSqlQuery q( db );

        if ( tst_Databases::isMSAccess( db ) )
            QVERIFY_SQL( q, exec( "create table " + qtest_precision + " (col1 number)" ) );
        else
            QVERIFY_SQL( q, exec( "create table " + qtest_precision + " (col1 numeric(21, 20))" ) );

        QVERIFY_SQL( q, exec( "insert into " + qtest_precision + " (col1) values (1.2345678901234567891)" ) );

        QVERIFY_SQL( q, exec( "select * from " + qtest_precision ) );
        QVERIFY( q.next() );

        QString val = q.value( 0 ).toString();

        if ( !val.startsWith( "1.2345678901234567891" ) ) {
            int i = 0;

            while ( precStr[i] != 0 && *( precStr + i ) == val[i].toLatin1() )
                i++;

            // MySQL and TDS have crappy precisions by default
            if ( db.driverName().startsWith( "QMYSQL" ) ) {
                if ( i < 17 )
                    QWARN( "MySQL didn't return the right precision" );
            } else if ( db.driverName().startsWith( "QTDS" ) ) {
                if ( i < 18 )
                    QWARN( "TDS didn't return the right precision" );
            } else {
                QWARN( QString( tst_Databases::dbToString( db ) + " didn't return the right precision (" +
                                QString::number( i ) + " out of 21), " + val ).toLatin1() );
            }
        }
    } // SQLITE scope
}

void tst_QSqlQuery::nullResult()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, exec( "select * from " + qtest + " where id > 50000" ) );

    if ( q.driver()->hasFeature( QSqlDriver::QuerySize ) )
        QCOMPARE( q.size(), 0 );

    QVERIFY( q.next() == false );

    QVERIFY( q.first() == false );
    QVERIFY( q.last() == false );
    QVERIFY( q.previous() == false );
    QVERIFY( q.seek( 10 ) == false );
    QVERIFY( q.seek( 0 ) == false );
}

// this test is just an experiment to see whether we can do query-based transactions
// the real transaction test is in tst_QSqlDatabase
void tst_QSqlQuery::transaction()
{
    // query based transaction is not really possible with Qt
    QSKIP( "only tested manually by trained staff", SkipAll );

    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::Transactions ) )
        QSKIP( "DBMS not transaction capable", SkipSingle );

    // this is the standard SQL
    QString startTransactionStr( "start transaction" );

    if ( db.driverName().startsWith( "QMYSQL" ) )
        startTransactionStr = "begin work";

    QSqlQuery q( db );

    QSqlQuery q2( db );

    // test a working transaction
    q.exec( startTransactionStr );

    QVERIFY_SQL( q, exec( "insert into" + qtest + " values (40, 'VarChar40', 'Char40')" ) );

    QVERIFY_SQL( q, exec( "select * from" + qtest + " where id = 40" ) );

    QVERIFY( q.next() );

    QCOMPARE( q.value( 0 ).toInt(), 40 );

    QVERIFY_SQL( q, exec( "commit" ) );

    QVERIFY_SQL( q, exec( "select * from" + qtest + " where id = 40" ) );

    QVERIFY( q.next() );

    QCOMPARE( q.value( 0 ).toInt(), 40 );

    // test a rollback
    q.exec( startTransactionStr );

    QVERIFY_SQL( q, exec( "insert into" + qtest + " values (41, 'VarChar41', 'Char41')" ) );

    QVERIFY_SQL( q, exec( "select * from" + qtest + " where id = 41" ) );

    QVERIFY( q.next() );

    QCOMPARE( q.value( 0 ).toInt(), 41 );

    if ( !q.exec( "rollback" ) ) {
        if ( db.driverName().startsWith( "QMYSQL" ) ) {
            qDebug( "MySQL: " + tst_Databases::printError( q.lastError() ) );
            QSKIP( "MySQL transaction failed ", SkipSingle ); //non-fatal
        } else
            QFAIL( "Could not rollback transaction: " + tst_Databases::printError( q.lastError() ) );
    }

    QVERIFY_SQL( q, exec( "select * from" + qtest + " where id = 41" ) );

    QVERIFY( q.next() == false );

    // test concurrent access
    q.exec( startTransactionStr );
    QVERIFY_SQL( q, exec( "insert into" + qtest + " values (42, 'VarChar42', 'Char42')" ) );
    QVERIFY_SQL( q, exec( "select * from" + qtest + " where id = 42" ) );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 42 );

    QVERIFY_SQL( q2, exec( "select * from" + qtest + " where id = 42" ) );

    if ( q2.next() )
        qDebug( QString( "DBMS '%1' doesn't support query based transactions with concurrent access" ).arg(
                    tst_Databases::dbToString( db ) ).toLatin1() );

    QVERIFY_SQL( q, exec( "commit" ) );

    QVERIFY_SQL( q2, exec( "select * from" + qtest + " where id = 42" ) );

    QVERIFY( q2.next() );

    QCOMPARE( q2.value( 0 ).toInt(), 42 );
}

void tst_QSqlQuery::joins()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtestj1(qTableName("qtestj1", __FILE__)), qtestj2(qTableName("qtestj2", __FILE__));

    if ( db.driverName().startsWith( "QOCI" )
            || db.driverName().startsWith( "QTDS" )
            || db.driverName().startsWith( "QODBC" )
            || db.driverName().startsWith( "QIBASE" ) ) {
        // Oracle broken beyond recognition - cannot outer join on more than
        // one table.
        QSKIP( "DBMS cannot understand standard SQL", SkipSingle );
        return;
    }

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "create table " + qtestj1 + " (id1 int, id2 int)" ) );
    QVERIFY_SQL( q, exec( "create table " + qtestj2 + " (id int, name varchar(20))" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtestj1 + " values (1, 1)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtestj1 + " values (1, 2)" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtestj2 + " values(1, 'trenton')" ) );
    QVERIFY_SQL( q, exec( "insert into " + qtestj2 + " values(2, 'marius')" ) );

    QVERIFY_SQL( q, exec( "select qtestj1.id1, qtestj1.id2, qtestj2.id, qtestj2.name, qtestj3.id, qtestj3.name "
                            "from " + qtestj1 + " qtestj1 left outer join " + qtestj2 +
                            " qtestj2 on (qtestj1.id1 = qtestj2.id) "
                            "left outer join " + qtestj2 + " as qtestj3 on (qtestj1.id2 = qtestj3.id)" ) );

    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toInt(), 1 );
    QCOMPARE( q.value( 2 ).toInt(), 1 );
    QCOMPARE( q.value( 3 ).toString(), QString( "trenton" ) );
    QCOMPARE( q.value( 4 ).toInt(), 1 );
    QCOMPARE( q.value( 5 ).toString(), QString( "trenton" ) );

    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toInt(), 2 );
    QCOMPARE( q.value( 2 ).toInt(), 1 );
    QCOMPARE( q.value( 3 ).toString(), QString( "trenton" ) );
    QCOMPARE( q.value( 4 ).toInt(), 2 );
    QCOMPARE( q.value( 5 ).toString(), QString( "marius" ) );
}

void tst_QSqlQuery::synonyms()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q(db);
    QVERIFY_SQL( q, exec("select a.id, a.t_char, a.t_varchar from " + qtest + " a where a.id = 1") );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toString().trimmed(), QString( "Char1" ) );
    QCOMPARE( q.value( 2 ).toString().trimmed(), QString( "VarChar1" ) );

    QSqlRecord rec = q.record();
    QCOMPARE(( int )rec.count(), 3 );
    QCOMPARE( rec.field( 0 ).name().toLower(), QString( "id" ) );
    QCOMPARE( rec.field( 1 ).name().toLower(), QString( "t_char" ) );
    QCOMPARE( rec.field( 2 ).name().toLower(), QString( "t_varchar" ) );
}

// It doesn't make sense to split this into several tests
void tst_QSqlQuery::prepare_bind_exec()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtest_prepare(qTableName("qtest_prepare", __FILE__));

    if(db.driverName().startsWith("QIBASE") && (db.databaseName() == "silence.nokia.troll.no:c:\\ibase\\testdb_ascii" || db.databaseName() == "/opt/interbase/qttest.gdb"))
        QSKIP("Can't transliterate extended unicode to ascii", SkipSingle);
    if(db.driverName().startsWith("QDB2"))
        QSKIP("Needs someone with more Unicode knowledge than I have to fix", SkipSingle);

    {
        // new scope for SQLITE
        static const QString utf8str = QString::fromUtf8( "काचं शक्नोम्यत्तुम् । नोपहिनस्ति माम् ॥" );

        static const QString values[6] = { "Harry", "Trond", "Mark", "Ma?rk", "?", ":id" };

        bool useUnicode = db.driver()->hasFeature( QSqlDriver::Unicode );

        QSqlQuery q( db );

        if ( db.driverName().startsWith( "QMYSQL" ) && tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
            useUnicode = false;

        QString createQuery;

        if(tst_Databases::isPostgreSQL(db))
            QVERIFY_SQL( q, exec("set client_min_messages='warning'"));

        if ( tst_Databases::isSqlServer( db ) || db.driverName().startsWith( "QTDS" ) )
            createQuery = "create table " + qtest_prepare + " (id int primary key, name nvarchar(200) null)";
        else if ( tst_Databases::isMySQL(db) && useUnicode )
            createQuery = "create table " + qtest_prepare + " (id int not null primary key, name varchar(200) character set utf8)";
        else
            createQuery = "create table " + qtest_prepare + " (id int not null primary key, name varchar(200))";

        QVERIFY_SQL( q, exec( createQuery ) );

        QVERIFY( q.prepare( "insert into " + qtest_prepare + " (id, name) values (:id, :name)" ) );
        int i;

        for ( i = 0; i < 6; ++i ) {
            q.bindValue( ":name", values[i] );
            q.bindValue( ":id", i );
            QVERIFY_SQL( q, exec() );
            QMap<QString, QVariant> m = q.boundValues();
            QCOMPARE(( int ) m.count(), 2 );
            QCOMPARE( m[":name"].toString(), values[i] );
            QCOMPARE( m[":id"].toInt(), i );
        }

        q.bindValue( ":id", 8 );

        QVERIFY_SQL( q, exec() );

        if ( useUnicode ) {
            q.bindValue( ":id", 7 );
            q.bindValue( ":name", utf8str );
            QVERIFY_SQL( q, exec() );
        }

        QVERIFY_SQL( q, exec( "SELECT * FROM " + qtest_prepare + " order by id" ) );

        for ( i = 0; i < 6; ++i ) {
            QVERIFY( q.next() );
            QCOMPARE( q.value( 0 ).toInt(), i );
            QCOMPARE( q.value( 1 ).toString().trimmed(), values[ i ] );
        }

        if ( useUnicode ) {
            QVERIFY_SQL( q, next() );
            QCOMPARE( q.value( 0 ).toInt(), 7 );
            QCOMPARE( q.value( 1 ).toString(), utf8str );
        }

        QVERIFY_SQL( q, next() );

        QCOMPARE( q.value( 0 ).toInt(), 8 );
        QCOMPARE( q.value( 1 ).toString(), values[5] );

        QVERIFY( q.prepare( "insert into " + qtest_prepare + " (id, name) values (:id, 'Bart')" ) );
        q.bindValue( ":id", 99 );
        QVERIFY_SQL( q, exec() );
        q.bindValue( ":id", 100 );
        QVERIFY_SQL( q, exec() );
        QVERIFY( q.exec( "select * from " + qtest_prepare + " where id > 98 order by id" ) );

        for ( i = 99; i <= 100; ++i ) {
            QVERIFY( q.next() );
            QCOMPARE( q.value( 0 ).toInt(), i );
            QCOMPARE( q.value( 1 ).toString().trimmed(), QString( "Bart" ) );
        }

        /*** SELECT stuff ***/
        QVERIFY( q.prepare( "select * from " + qtest_prepare + " where id = :id" ) );

        for ( i = 0; i < 6; ++i ) {
            q.bindValue( ":id", i );
            QVERIFY_SQL( q, exec() );
            QVERIFY_SQL( q, next() );
            QCOMPARE( q.value( 0 ).toInt(), i );
            QCOMPARE( q.value( 1 ).toString().trimmed(), values[ i ] );
            QSqlRecord rInf = q.record();
            QCOMPARE(( int )rInf.count(), 2 );
            QCOMPARE( rInf.field( 0 ).name().toUpper(), QString( "ID" ) );
            QCOMPARE( rInf.field( 1 ).name().toUpper(), QString( "NAME" ) );
            QVERIFY( !q.next() );
        }

        QVERIFY_SQL( q, exec( "DELETE FROM " + qtest_prepare ) );

        QVERIFY( q.prepare( "insert into " + qtest_prepare + " (id, name) values (?, ?)" ) );
        q.bindValue( 0, 0 );
        q.bindValue( 1, values[ 0 ] );
        QVERIFY_SQL( q, exec() );
        q.addBindValue( 1 );
        q.addBindValue( values[ 1 ] );
        QVERIFY_SQL( q, exec() );
        q.addBindValue( 2 );
        q.addBindValue( values[ 2 ] );
        QVERIFY_SQL( q, exec() );
        q.addBindValue( 3 );
        q.addBindValue( values[ 3 ] );
        QVERIFY_SQL( q, exec() );
        q.addBindValue( 4 );
        q.addBindValue( values[ 4 ] );
        QVERIFY_SQL( q, exec() );
        q.bindValue( 1, values[ 5 ] );
        q.bindValue( 0, 5 );
        QVERIFY_SQL( q, exec() );
        q.bindValue( 0, 6 );
        q.bindValue( 1, QString() );
        QVERIFY_SQL( q, exec() );

        if ( db.driver()->hasFeature( QSqlDriver::Unicode ) ) {
            q.bindValue( 0, 7 );
            q.bindValue( 1, utf8str );
            QVERIFY_SQL( q, exec() );
        }

        QVERIFY_SQL( q, exec( "SELECT * FROM " + qtest_prepare + " order by id" ) );

        for ( i = 0; i < 6; ++i ) {
            QVERIFY( q.next() );
            QCOMPARE( q.value( 0 ).toInt(), i );
            QCOMPARE( q.value( 1 ).toString().trimmed(), values[ i ] );
        }

        QVERIFY( q.next() );

        QCOMPARE( q.value( 0 ).toInt(), 6 );
        QVERIFY( q.isNull( 1 ) );

        if ( useUnicode ) {
            QVERIFY( q.next() );
            QCOMPARE( q.value( 0 ).toInt(), 7 );
            QCOMPARE( q.value( 1 ).toString(), utf8str );
        }

        QVERIFY( q.prepare( "insert into " + qtest_prepare + " (id, name) values (?, 'Bart')" ) );

        q.bindValue( 0, 99 );
        QVERIFY_SQL( q, exec() );
        q.addBindValue( 100 );
        QVERIFY_SQL( q, exec() );
        QVERIFY( q.exec( "select * from " + qtest_prepare + " where id > 98 order by id" ) );

        for ( i = 99; i <= 100; ++i ) {
            QVERIFY( q.next() );
            QCOMPARE( q.value( 0 ).toInt(), i );
            QCOMPARE( q.value( 1 ).toString().trimmed(), QString( "Bart" ) );
        }

        /* insert a duplicate id and make sure the db bails out */
        QVERIFY( q.prepare( "insert into " + qtest_prepare + " (id, name) values (?, ?)" ) );

        q.addBindValue( 99 );

        q.addBindValue( "something silly" );

        QVERIFY( !q.exec() );

        QVERIFY( q.lastError().isValid() );

        QVERIFY( !q.isActive() );

    } // end of SQLite scope
}

void tst_QSqlQuery::prepared_select()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, prepare( "select a.id, a.t_char, a.t_varchar from " + qtest + " a where a.id = ?" ) );

    q.bindValue( 0, 1 );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.at(), ( int )QSql::BeforeFirstRow );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );

    q.bindValue( 0, 2 );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.at(), ( int )QSql::BeforeFirstRow );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 2 );

    q.bindValue( 0, 3 );
    QVERIFY_SQL( q, exec() );
    QCOMPARE( q.at(), ( int )QSql::BeforeFirstRow );
    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 3 );

    QVERIFY_SQL( q, prepare( "select a.id, a.t_char, a.t_varchar from " + qtest + " a where a.id = ?" ) );
    QCOMPARE( q.at(), ( int )QSql::BeforeFirstRow );
    QVERIFY( !q.first() );
}

void tst_QSqlQuery::sqlServerLongStrings()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !tst_Databases::isSqlServer( db ) )
        QSKIP( "SQL Server specific test", SkipSingle );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "CREATE TABLE " + qTableName( "qtest_longstr", __FILE__ ) + " (id int primary key, longstring ntext)" ) );

    QVERIFY_SQL( q, prepare( "INSERT INTO " + qTableName( "qtest_longstr", __FILE__ ) + " VALUES (?, ?)" ) );

    q.addBindValue( 0 );

    q.addBindValue( QString::fromLatin1( "bubu" ) );

    QVERIFY_SQL( q, exec() );

    QString testStr;

    testStr.fill( QLatin1Char( 'a' ), 85000 );

    q.addBindValue( 1 );

    q.addBindValue( testStr );

    QVERIFY_SQL( q, exec() );

    QVERIFY_SQL( q, exec( "select * from " + qTableName( "qtest_longstr", __FILE__ ) ) );

    QVERIFY_SQL( q, next() );

    QCOMPARE( q.value( 0 ).toInt(), 0 );

    QCOMPARE( q.value( 1 ).toString(), QString::fromLatin1( "bubu" ) );

    QVERIFY_SQL( q, next() );

    QCOMPARE( q.value( 0 ).toInt(), 1 );

    QCOMPARE( q.value( 1 ).toString(), testStr );
}

void tst_QSqlQuery::invalidQuery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );

    QVERIFY( !q.exec() );

    QVERIFY( !q.exec( "blahfasel" ) );
    QVERIFY( q.lastError().type() != QSqlError::NoError );
    QVERIFY( !q.next() );
    QVERIFY( !q.isActive() );

    if ( !db.driverName().startsWith( "QOCI" ) && !db.driverName().startsWith( "QDB2" ) && !db.driverName().startsWith( "QODBC" ) ) {
        // oracle and db2 just prepares everything without complaining
        if ( db.driver()->hasFeature( QSqlDriver::PreparedQueries ) )
            QVERIFY( !q.prepare( "blahfasel" ) );
    }

    QVERIFY( !q.exec() );

    QVERIFY( !q.isActive() );
    QVERIFY( !q.next() );
}

class ResultHelper: public QSqlResult
{

public:
    ResultHelper(): QSqlResult( 0 ) {} // don't call, it's only for stupid compilers

    bool execBatch( bool bindArray = false )
    {
        return QSqlResult::execBatch( bindArray );
    }
};

void tst_QSqlQuery::batchExec()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::BatchOperations ) )
        QSKIP( "Database can't do BatchOperations", SkipSingle );

    QSqlQuery q( db );
    const QString tableName = qTableName( "qtest_batch", __FILE__ );

    QVERIFY_SQL( q, exec( "create table " + tableName + " (id int, name varchar(20), dt date, num numeric(8, 4))" ) );
    QVERIFY_SQL( q, prepare( "insert into " + tableName + " (id, name, dt, num) values (?, ?, ?, ?)" ) );

    QVariantList intCol;
    intCol << 1 << 2 << QVariant( QVariant::Int );

    QVariantList charCol;
    charCol << QLatin1String( "harald" ) << QLatin1String( "boris" ) << QVariant( QVariant::String );

    QVariantList dateCol;
    QDateTime dt = QDateTime( QDate::currentDate(), QTime( 1, 2, 3 ) );
    dateCol << dt << dt.addDays( -1 ) << QVariant( QVariant::DateTime );

    QVariantList numCol;
    numCol << 2.3 << 3.4 << QVariant( QVariant::Double );

    q.addBindValue( intCol );
    q.addBindValue( charCol );
    q.addBindValue( dateCol );
    q.addBindValue( numCol );

    QVERIFY_SQL( q, execBatch() );
    QVERIFY_SQL( q, exec( "select id, name, dt, num from " + tableName + " order by id" ) );

    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toString(), QString( "harald" ) );
    QCOMPARE( q.value( 2 ).toDateTime(), dt );
    QCOMPARE( q.value( 3 ).toDouble(), 2.3 );

    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 2 );
    QCOMPARE( q.value( 1 ).toString(), QString( "boris" ) );
    QCOMPARE( q.value( 2 ).toDateTime(), dt.addDays( -1 ) );
    QCOMPARE( q.value( 3 ).toDouble(), 3.4 );

    QVERIFY( q.next() );
    QVERIFY( q.value( 0 ).isNull() );
    QVERIFY( q.value( 1 ).isNull() );
    QVERIFY( q.value( 2 ).isNull() );
    QVERIFY( q.value( 3 ).isNull() );
}

void tst_QSqlQuery::oraArrayBind()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::BatchOperations ) )
        QSKIP( "Database can't do BatchOperations", SkipSingle );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "CREATE OR REPLACE PACKAGE ora_array_test "
                            "IS "
                            "TYPE names_type IS TABLE OF VARCHAR(64) NOT NULL INDEX BY BINARY_INTEGER; "
                            "names_tab names_type; "
                            "PROCEDURE set_name(name_in IN VARCHAR2, row_in in INTEGER); "
                            "PROCEDURE get_name(row_in IN INTEGER, str_out OUT VARCHAR2); "
                            "PROCEDURE get_table(tbl OUT names_type); "
                            "PROCEDURE set_table(tbl IN names_type); "
                            "END ora_array_test; " ) );

    QVERIFY_SQL( q, exec( "CREATE OR REPLACE PACKAGE BODY ora_array_test "
                            "IS "
                            "PROCEDURE set_name(name_in IN VARCHAR2, row_in in INTEGER) "
                            "IS "
                            "BEGIN "
                            "names_tab(row_in) := name_in; "
                            "END set_name; "

                            "PROCEDURE get_name(row_in IN INTEGER, str_out OUT VARCHAR2) "
                            "IS "
                            "BEGIN "
                            "str_out := names_tab(row_in); "
                            "END get_name; "

                            "PROCEDURE get_table(tbl OUT names_type) "
                            "IS "
                            "BEGIN "
                            "tbl:=names_tab; "
                            "END get_table; "

                            "PROCEDURE set_table(tbl IN names_type) "
                            "IS "
                            "BEGIN "
                            "names_tab := tbl; "
                            "END set_table; "
                            "END ora_array_test; " ) );

    QVariantList list;

    list << QString( "lorem" ) << QString( "ipsum" ) << QString( "dolor" ) << QString( "sit" ) << QString( "amet" );

    QVERIFY_SQL( q, prepare( "BEGIN "
                               "ora_array_test.set_table(?); "
                               "END;" ) );

    q.bindValue( 0, list, QSql::In );

    QVERIFY_SQL( q, execBatch( QSqlQuery::ValuesAsColumns ) );

    QVERIFY_SQL( q, prepare( "BEGIN "
                               "ora_array_test.get_table(?); "
                               "END;" ) );

    list.clear();

    list << QString( 64,' ' ) << QString( 64,' ' ) << QString( 64,' ' ) << QString( 64,' ' ) << QString( 64,' ' );

    q.bindValue( 0, list, QSql::Out );

    QVERIFY_SQL( q, execBatch( QSqlQuery::ValuesAsColumns ) );

    QVariantList out_list = q.boundValue( 0 ).toList();

    QCOMPARE( out_list.at( 0 ).toString(), QString( "lorem" ) );

    QCOMPARE( out_list.at( 1 ).toString(), QString( "ipsum" ) );

    QCOMPARE( out_list.at( 2 ).toString(), QString( "dolor" ) );

    QCOMPARE( out_list.at( 3 ).toString(), QString( "sit" ) );

    QCOMPARE( out_list.at( 4 ).toString(), QString( "amet" ) );

    QVERIFY_SQL( q, exec( "DROP PACKAGE ora_array_test" ) );
}

/*
    Tests that QSqlDatabase::record and QSqlQuery::record returns the same thing
    otherwise our models get confused.
 */
void tst_QSqlQuery::record_sqlite()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "create table "+qTableName( "record_sqlite", __FILE__ )+"(id integer primary key, name varchar, title int)" ) );

    QSqlRecord rec = db.record( qTableName( "record_sqlite", __FILE__ ) );

    QCOMPARE( rec.count(), 3 );
    QCOMPARE( rec.field( 0 ).type(), QVariant::Int );
    QCOMPARE( rec.field( 1 ).type(), QVariant::String );
    QCOMPARE( rec.field( 2 ).type(), QVariant::Int );

    /* important - select from an empty table */
    QVERIFY_SQL( q, exec( "select id, name, title from "+qTableName( "record_sqlite", __FILE__ ) ) );

    rec = q.record();
    QCOMPARE( rec.count(), 3 );
    QCOMPARE( rec.field( 0 ).type(), QVariant::Int );
    QCOMPARE( rec.field( 1 ).type(), QVariant::String );
    QCOMPARE( rec.field( 2 ).type(), QVariant::Int );
}

void tst_QSqlQuery::oraLong()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );

    QString aLotOfText( 127000, QLatin1Char( 'H' ) );

    QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_longstr", __FILE__ ) + " (id int primary key, astr long)" ) );
    QVERIFY_SQL( q, prepare( "insert into " + qTableName( "qtest_longstr", __FILE__ ) + " (id, astr) values (?, ?)" ) );
    q.addBindValue( 1 );
    q.addBindValue( aLotOfText );
    QVERIFY_SQL( q, exec() );

    QVERIFY_SQL( q, exec( "select id,astr from " + qTableName( "qtest_longstr", __FILE__ ) ) );

    QVERIFY( q.next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toString(), aLotOfText );
}

void tst_QSqlQuery::execErrorRecovery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_exerr", __FILE__ ) + " (id int not null primary key)" ) );
    QVERIFY_SQL( q, prepare( "insert into " + qTableName( "qtest_exerr", __FILE__ ) + " values (?)" ) );

    q.addBindValue( 1 );
    QVERIFY_SQL( q, exec() );

    q.addBindValue( 1 ); // binding the same pkey - should fail
    QVERIFY( !q.exec() );

    q.addBindValue( 2 ); // this should work again
    QVERIFY_SQL( q, exec() );
}

void tst_QSqlQuery::lastInsertId()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::LastInsertId ) )
        QSKIP( "Database doesn't support lastInsertId", SkipSingle );

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "insert into " + qtest + " values (41, 'VarChar41', 'Char41')" ) );

    QVariant v = q.lastInsertId();

    QVERIFY( v.isValid() );
}

void tst_QSqlQuery::lastQuery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QString sql = "select * from " + qtest;
    QVERIFY_SQL( q, exec( sql ) );
    QCOMPARE( q.lastQuery(), sql );
    QCOMPARE( q.executedQuery(), sql );
}

void tst_QSqlQuery::bindWithDoubleColonCastOperator()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    // Only PostgreSQL support the double-colon cast operator

    if ( !db.driverName().startsWith( "QPSQL" ) ) {
        QSKIP( "Test requires PostgreSQL", SkipSingle );
        return;
    }

    const QString tablename(qTableName( "bindtest", __FILE__ ));

    QSqlQuery q( db );

    QVERIFY_SQL( q, exec( "create table " + tablename + " (id1 int, id2 int, id3 int, fld1 int, fld2 int)" ) );
    QVERIFY_SQL( q, exec( "insert into " + tablename + " values (1, 2, 3, 10, 5)" ) );

    QVERIFY_SQL( q, prepare( "select sum((fld1 - fld2)::int) from " + tablename + " where id1 = :myid1 and id2 =:myid2 and id3=:myid3" ) );
    q.bindValue( ":myid1", 1 );
    q.bindValue( ":myid2", 2 );
    q.bindValue( ":myid3", 3 );

    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, next() );

    if ( db.driver()->hasFeature( QSqlDriver::PreparedQueries ) )
        QCOMPARE( q.executedQuery(), QString( "select sum((fld1 - fld2)::int) from " + tablename + " where id1 = ? and id2 =? and id3=?" ) );
    else
        QCOMPARE( q.executedQuery(), QString( "select sum((fld1 - fld2)::int) from " + tablename + " where id1 = 1 and id2 =2 and id3=3" ) );
}

/* For task 157397: Using QSqlQuery with an invalid QSqlDatabase
   does not set the last error of the query.
   This test function will output some warnings, that's ok.
*/
void tst_QSqlQuery::queryOnInvalidDatabase()
{
    {
        QTest::ignoreMessage( QtWarningMsg, "QSqlDatabase: INVALID driver not loaded" );
        QSqlDatabase db = QSqlDatabase::addDatabase( "INVALID", "invalidConnection" );
        QVERIFY2( db.lastError().isValid(),
                  qPrintable( QString( "db.lastError().isValid() should be true!" ) ) );

        QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::exec: database not open" );
        QSqlQuery query( "SELECT 1 AS ID", db );
        QVERIFY2( query.lastError().isValid(),
                  qPrintable( QString( "query.lastError().isValid() should be true!" ) ) );
    }

    QSqlDatabase::removeDatabase( "invalidConnection" );

    {
        QSqlDatabase db = QSqlDatabase::database( "this connection does not exist" );
        QTest::ignoreMessage( QtWarningMsg, "QSqlQuery::exec: database not open" );
        QSqlQuery query( "SELECT 1 AS ID", db );
        QVERIFY2( query.lastError().isValid(),
                  qPrintable( QString( "query.lastError().isValid() should be true!" ) ) );
    }
}

/* For task 159138: Error on instantiating a sql-query before explicitly
   opening the database. This is something we don't support, so this isn't
   really a bug. However some of the drivers are nice enough to support it.
*/
void tst_QSqlQuery::createQueryOnClosedDatabase()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    // Only supported by these drivers

    if ( !db.driverName().startsWith( "QPSQL" )
            && !db.driverName().startsWith( "QOCI" )
            && !db.driverName().startsWith( "QMYSQL" )
            && !db.driverName().startsWith( "QDB2" ) ) {
        QSKIP( "Test is specific for PostgreSQL, Oracle, MySql and DB2", SkipSingle );
        return;
    }

    db.close();

    QSqlQuery q( db );
    db.open();
    QVERIFY_SQL( q, exec( QString( "select * from %1 where id = 1" ).arg( qtest ) ) );

    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toString().trimmed(), QLatin1String( "VarChar1" ) );
    QCOMPARE( q.value( 2 ).toString().trimmed(), QLatin1String( "Char1" ) );

    db.close();
    QVERIFY2( !q.exec( QString( "select * from %1 where id = 1" ).arg( qtest ) ),
              qPrintable( QString( "This can't happen! The query should not have been executed!" ) ) );
}

void tst_QSqlQuery::reExecutePreparedForwardOnlyQuery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    q.setForwardOnly( true );

    QVERIFY_SQL( q, prepare( QString( "SELECT id, t_varchar, t_char FROM %1 WHERE id = :id" ).arg( qtest ) ) );
    q.bindValue( ":id", 1 );
    QVERIFY_SQL( q, exec() );

    // Do something, like iterate over the result, or skip to the end
    QVERIFY_SQL( q, last() );

    QVERIFY_SQL( q, exec() );
    /* This was broken with SQLite because the cache size was set to 0 in the 2nd execute.
       When forwardOnly is set we don't cahce the entire result, but we do cache the current row
       but this requires the cache size to be equal to the column count.
    */
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.value( 1 ).toString().trimmed(), QString( "VarChar1" ) );
    QCOMPARE( q.value( 2 ).toString().trimmed(), QString( "Char1" ) );
}

void tst_QSqlQuery::finish()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    QVERIFY_SQL( q, prepare( "SELECT id FROM " + qtest + " WHERE id = ?" ) );

    int id = 4;
    q.bindValue( 0, id );
    QVERIFY_SQL( q, exec() );
    QVERIFY( q.isActive() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), id );

    q.finish();
    QVERIFY( !q.isActive() ); // query is now inactive
    QCOMPARE( q.boundValue( 0 ).toInt(), id ); // bound values are retained

    QVERIFY_SQL( q, exec() ); // no prepare necessary
    QVERIFY( q.isActive() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), id );

    q.finish();
    QVERIFY( !q.isActive() );

    QVERIFY_SQL( q, exec( "SELECT id FROM " + qtest + " WHERE id = 1" ) );
    QVERIFY( q.isActive() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toInt(), 1 );
    QCOMPARE( q.record().count(), 1 );
}

void tst_QSqlQuery::sqlite_finish()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if (db.driverName() != QLatin1String("QSQLITE")) {
        QSKIP("Sqlite3 specific test", SkipSingle);
        return;
    }

    if ( db.databaseName().startsWith( ':' ) )
        QSKIP( "This test requires a database on the filesystem, not in-memory", SkipAll );

    {
        QSqlDatabase db2 = QSqlDatabase::addDatabase( "QSQLITE", "sqlite_finish_sqlite" );
        db2.setDatabaseName( db.databaseName() );
        QVERIFY_SQL( db2, open() );

        const QString tableName(qTableName( "qtest_lockedtable", __FILE__ ));
        QSqlQuery q( db );

        tst_Databases::safeDropTable( db, tableName );
        q.exec( "CREATE TABLE " + tableName + " (pk_id INTEGER PRIMARY KEY, whatever TEXT)" );
        q.exec( "INSERT INTO " + tableName + " values(1, 'whatever')" );
        q.exec( "INSERT INTO " + tableName + " values(2, 'whatever more')" );

        // This creates a read-lock in the database
        QVERIFY_SQL( q, exec( "SELECT * FROM " + tableName + " WHERE pk_id = 1 or pk_id = 2" ) );
        QVERIFY_SQL( q, next() );

        // The DELETE will fail because of the read-lock
        QSqlQuery q2( db2 );
        QVERIFY( !q2.exec( "DELETE FROM " + tableName + " WHERE pk_id=2" ) );
        QCOMPARE( q2.numRowsAffected(), -1 );

        // The DELETE will succeed now because finish() removes the lock
        q.finish();
        QVERIFY_SQL( q2, exec( "DELETE FROM " + tableName + " WHERE pk_id=2" ) );
        QCOMPARE( q2.numRowsAffected(), 1 );

        tst_Databases::safeDropTable( db, tableName );
    }

    QSqlDatabase::removeDatabase( "sqlite_finish_sqlite" );
}

void tst_QSqlQuery::nextResult()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::MultipleResultSets ) || !db.driver()->hasFeature( QSqlDriver::BatchOperations ) )
        QSKIP( "DBMS does not support multiple result sets or batch operations", SkipSingle );

    QSqlQuery q( db );

    if ( db.driverName().startsWith( "QMYSQL" ) && tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
        QSKIP( "Test requires MySQL >= 5.0", SkipSingle );

    enum DriverType { ODBC, MYSQL, DB2 };
    DriverType driverType = ODBC;

    if ( db.driverName().startsWith( "QMYSQL" ) )
        driverType = MYSQL;
    else if ( db.driverName().startsWith( "QDB2" ) )
        driverType = DB2;

    const QString tableName(qTableName( "more_results", __FILE__ ));

    QVERIFY_SQL( q, exec( "CREATE TABLE " + tableName + " (id integer, text varchar(20), num numeric(6, 3), empty varchar(10));" ) );

    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " VALUES(1, 'one', 1.1, '');" ) );

    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " VALUES(2, 'two', 2.2, '');" ) );

    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " VALUES(3, 'three', 3.3, '');" ) );

    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " VALUES(4, 'four', 4.4, '');" ) );

    QStringList tstStrings;

    tstStrings << "one" << "two" << "three" << "four";

    // Query that returns only one result set, nothing special about this
    QVERIFY_SQL( q, exec( QString( "SELECT * FROM %1;" ).arg( tableName ) ) );

    QVERIFY( q.next() );                // Move to first row of the result set

    QVERIFY( !q.nextResult() );         // No more result sets are available

    QVERIFY( !q.isActive() );           // So the query is no longer active

    QVERIFY( !q.next() );               // ... and no data is available as the call

    // to nextResult() discarded the result set

    // Query that returns two result sets (batch sql)
    // When working with multiple result sets SQL Server insists on non-scrollable cursors
    if ( driverType == ODBC )
        q.setForwardOnly( true );

    QVERIFY_SQL( q, exec( "SELECT id FROM " + tableName + "; SELECT text, num FROM " + tableName + ';' ) );

    QCOMPARE( q.record().count(), 1 );  // Check that the meta data is as expected

    QCOMPARE( q.record().field( 0 ).name().toUpper(), QString( "ID" ) );

    QCOMPARE( q.record().field( 0 ).type(), QVariant::Int );

    QVERIFY( q.nextResult() );          // Discards first result set and move to the next

    QCOMPARE( q.record().count(), 2 );  // New meta data should be available

    QCOMPARE( q.record().field( 0 ).name().toUpper(), QString( "TEXT" ) );

    QCOMPARE( q.record().field( 0 ).type(), QVariant::String );

    QCOMPARE( q.record().field( 1 ).name().toUpper(), QString( "NUM" ) );

    if ( driverType == MYSQL )
        QCOMPARE( q.record().field( 1 ).type(), QVariant::String );
    else
        QCOMPARE( q.record().field( 1 ).type(), QVariant::Double );

    QVERIFY( q.next() );                    // Move to first row of the second result set

    QFAIL_SQL(q, nextResult()); // No more result sets after this

    QVERIFY( !q.isActive() );               // So the query is no longer active

    QVERIFY( !q.next() );                   // ... and no data is available as the call to

    // nextResult() discarded the result set

    // Query that returns one result set, a count of affected rows and then another result set
    QString query1 = QString( "SELECT id, text, num, empty FROM %1 WHERE id <= 3" ).arg( tableName );

    QString query2 = QString( "UPDATE %1 SET empty = 'Yatta!'" ).arg( tableName );

    QString query3 = QString( "SELECT id, empty FROM %1 WHERE id <=2" ).arg( tableName );

    QVERIFY_SQL( q, exec( QString( "%1; %2; %3;" ).arg( query1 ).arg( query2 ).arg( query3 ) ) );

    // Check result set returned by first statement
    QVERIFY( q.isSelect() );            // The first statement is a select

    for ( int i = 0; i < 3; i++ ) {
        QVERIFY_SQL( q, next() );
        QCOMPARE( q.value( 0 ).toInt(), 1+i );
        QCOMPARE( q.value( 1 ).toString(), tstStrings.at( i ) );
        QCOMPARE( q.value( 2 ).toDouble(), 1.1*( i+1 ) );
        QVERIFY( q.value( 3 ).toString().isEmpty() );
    }

    QVERIFY_SQL( q, nextResult() );

    QVERIFY( !q.isSelect() );           // The second statement isn't a SELECT
    QVERIFY( !q.next() );               // ... so no result set is available
    QCOMPARE( q.numRowsAffected(), 4 ); // 4 rows was affected by the UPDATE

    // Check result set returned by third statement
    QVERIFY_SQL( q, nextResult() );
    QVERIFY( q.isSelect() );            // The third statement is a SELECT

    for ( int i = 0; i < 2; i++ ) {
        QVERIFY_SQL( q, next() );
        QCOMPARE( q.value( 0 ).toInt(), 1+i );
        QCOMPARE( q.value( 1 ).toString(), QString( "Yatta!" ) );
    }

    // Stored procedure with multiple result sets
    const QString procName(qTableName( "proc_more_res", __FILE__ ));

    q.exec( QString( "DROP PROCEDURE %1;" ).arg( procName ) );

    if ( driverType == MYSQL )
        QVERIFY_SQL( q, exec( QString( "CREATE PROCEDURE %1()"
                                         "\nBEGIN"
                                         "\nSELECT id, text FROM %2;"
                                         "\nSELECT empty, num, text, id FROM %3;"
                                         "\nEND" ).arg( procName ).arg( tableName ).arg( tableName ) ) );
    else if ( driverType == DB2 )
        QVERIFY_SQL( q, exec( QString( "CREATE PROCEDURE %1()"
                                         "\nRESULT SETS 2"
                                         "\nLANGUAGE SQL"
                                         "\np1:BEGIN"
                                         "\nDECLARE cursor1 CURSOR WITH RETURN FOR SELECT id, text FROM %2;"
                                         "\nDECLARE cursor2 CURSOR WITH RETURN FOR SELECT empty, num, text, id FROM %3;"
                                         "\nOPEN cursor1;"
                                         "\nOPEN cursor2;"
                                         "\nEND p1" ).arg( procName ).arg( tableName ).arg( tableName ) ) );
    else
        QVERIFY_SQL( q, exec( QString( "CREATE PROCEDURE %1"
                                         "\nAS"
                                         "\nSELECT id, text FROM %2"
                                         "\nSELECT empty, num, text, id FROM %3" ).arg( procName ).arg( tableName ).arg( tableName ) ) );

    if ( driverType == MYSQL || driverType == DB2 ) {
        q.setForwardOnly( true );
        QVERIFY_SQL( q, exec( QString( "CALL %1()" ).arg( procName ) ) );
    } else {
        QVERIFY_SQL( q, exec( QString( "EXEC %1" ).arg( procName ) ) );
    }

    for ( int i = 0; i < 4; i++ ) {
        QVERIFY_SQL( q, next() );
        QCOMPARE( q.value( 0 ).toInt(), i+1 );
        QCOMPARE( q.value( 1 ).toString(), tstStrings.at( i ) );
    }

    QVERIFY_SQL( q, nextResult() );

    QVERIFY_SQL( q, isActive() );

    for ( int i = 0; i < 4; i++ ) {
        QVERIFY_SQL( q, next() );
        QCOMPARE( q.value( 0 ).toString(), QString( "Yatta!" ) );
        QCOMPARE( q.value( 1 ).toDouble(), 1.1*( 1+i ) );
        QCOMPARE( q.value( 2 ).toString(), tstStrings.at( i ) );
        QCOMPARE( q.value( 3 ).toInt(), 1+i );
    }

    // MySQL also counts the CALL itself as a result
    if ( driverType == MYSQL ) {
        QVERIFY( q.nextResult() );
        QVERIFY( !q.isSelect() );           // ... but it's not a select
        QCOMPARE( q.numRowsAffected(), 0 ); // ... and no rows are affected (at least not with this procedure)
    }

    QVERIFY( !q.nextResult() );

    QVERIFY( !q.isActive() );

    q.exec( QString( "DROP PROCEDURE %1;" ).arg( procName ) );
}


// For task 190311. Problem: Truncation happens on the 2nd execution if that BLOB is larger
// than the BLOB on the 1st execution. This was only for MySQL, but the test is general
// enough to be run with all backends.
void tst_QSqlQuery::blobsPreparedQuery()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if ( !db.driver()->hasFeature( QSqlDriver::BLOB ) || !db.driver()->hasFeature( QSqlDriver::PreparedQueries ) )
        QSKIP( "DBMS does not support BLOBs or prepared queries", SkipSingle );

    const QString tableName(qTableName( "blobstest", __FILE__ ));

    QSqlQuery q( db );
    q.setForwardOnly( true ); // This is needed to make the test work with DB2.
    QString shortBLOB( "abc" );
    QString longerBLOB( "abcdefghijklmnopqrstuvxyz¿äëïöü¡  " );

    // In PostgreSQL a BLOB is not called a BLOB, but a BYTEA! :-)
    // ... and in SQL Server it can be called a lot, but IMAGE will do.
    QString typeName( "BLOB" );
    if ( db.driverName().startsWith( "QPSQL" ) )
        typeName = "BYTEA";
    else if ( db.driverName().startsWith( "QODBC" ) && tst_Databases::isSqlServer( db ))
        typeName = "IMAGE";

    QVERIFY_SQL( q, exec( QString( "CREATE TABLE %1(id INTEGER, data %2)" ).arg( tableName ).arg( typeName ) ) );
    q.prepare( QString( "INSERT INTO %1(id, data) VALUES(:id, :data)" ).arg( tableName ) );
    q.bindValue( ":id", 1 );
    q.bindValue( ":data", shortBLOB.toAscii() );
    QVERIFY_SQL( q, exec() );

    q.bindValue( ":id", 2 );
    q.bindValue( ":data", longerBLOB.toAscii() );
    QVERIFY_SQL( q, exec() );

    // Two executions and result sets
    q.prepare( QString( "SELECT data FROM %1 WHERE id = ?" ).arg( tableName ) );
    q.bindValue( 0, QVariant( 1 ) );
    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toString(), shortBLOB );

    q.bindValue( 0, QVariant( 2 ) );
    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toString(), longerBLOB );

    // Only one execution and result set
    q.prepare( QString( "SELECT id, data FROM %1 ORDER BY id" ).arg( tableName ) );
    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 1 ).toString(), shortBLOB );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 1 ).toString(), longerBLOB );
}

// There were problems with navigating past the end of a table returning an error on mysql
void tst_QSqlQuery::emptyTableNavigate()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    {
        QSqlQuery q( db );
        QVERIFY_SQL( q, exec( "create table " + qTableName( "qtest_empty", __FILE__ ) + " (id char(10))" ) );
        QVERIFY_SQL( q, prepare( "select * from " + qTableName( "qtest_empty", __FILE__ ) ) );
        QVERIFY_SQL( q, exec() );
        QVERIFY( !q.next() );
        QCOMPARE( q.lastError().isValid(), false );
    }
}

void tst_QSqlQuery::task_217003()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    QSqlQuery q( db );
    const QString Planet(qTableName( "Planet", __FILE__));

    QVERIFY_SQL( q, exec( "create table " + Planet + " (Name varchar(20))" ) );
    QVERIFY_SQL( q, exec( "insert into " + Planet + " VALUES ('Mercury')" ) );
    QVERIFY_SQL( q, exec( "insert into " + Planet + " VALUES ('Venus')" ) );
    QVERIFY_SQL( q, exec( "insert into " + Planet + " VALUES ('Earth')" ) );
    QVERIFY_SQL( q, exec( "insert into " + Planet + " VALUES ('Mars')" ) );

    QVERIFY_SQL( q, exec( "SELECT Name FROM " + Planet ) );
    QVERIFY_SQL( q, seek( 3 ) );
    QCOMPARE( q.value( 0 ).toString(), QString( "Mars" ) );
    QVERIFY_SQL( q, seek( 1 ) );
    QCOMPARE( q.value( 0 ).toString(), QString( "Venus" ) );
    QVERIFY_SQL( q, exec( "SELECT Name FROM " + Planet ) );
    QVERIFY_SQL( q, seek( 3 ) );
    QCOMPARE( q.value( 0 ).toString(), QString( "Mars" ) );
    QVERIFY_SQL( q, seek( 0 ) );
    QCOMPARE( q.value( 0 ).toString(), QString( "Mercury" ) );
    QVERIFY_SQL( q, seek( 1 ) );
    QCOMPARE( q.value( 0 ).toString(), QString( "Venus" ) );
}

void tst_QSqlQuery::task_250026()
{
    QString data258, data1026;
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    QSqlQuery q( db );

    const QString tableName(qTableName( "task_250026", __FILE__ ));

    if ( !q.exec( "create table " + tableName + " (longfield varchar(1100))" ) ) {
        qDebug() << "Error" << q.lastError();
        QSKIP( "Db doesn't support \"1100\" as a size for fields", SkipSingle );
    }

    data258.fill( 'A', 258 );
    data1026.fill( 'A', 1026 );
    QVERIFY_SQL( q, prepare( "insert into " + tableName + "(longfield) VALUES (:longfield)" ) );
    q.bindValue( "longfield", data258 );
    QVERIFY_SQL( q, exec() );
    q.bindValue( "longfield", data1026 );
    QVERIFY_SQL( q, exec() );
    QVERIFY_SQL( q, exec( "select * from " + tableName ) );
    QVERIFY_SQL( q, next() );
    QCOMPARE( q.value( 0 ).toString().length(), data258.length() );
    QVERIFY_SQL( q, next() );
	QCOMPARE( q.value( 0 ).toString().length(), data1026.length() );
}

void tst_QSqlQuery::task_205701()
{
    QSqlDatabase qsdb = QSqlDatabase::addDatabase("QMYSQL", "atest");
    qsdb.setHostName("test");
    qsdb.setDatabaseName("test");
    qsdb.setUserName("test");
    qsdb.setPassword("test");
    qsdb.open();

//     {
        QSqlQuery query(qsdb);
//     }
    QSqlDatabase::removeDatabase("atest");
}

#ifdef NOT_READY_YET
// For task: 229811
void tst_QSqlQuery::task_229811()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if (!db.driverName().startsWith( "QODBC" )) return;

    QSqlQuery q( db );

    const QString tableName(qTableName( "task_229811", __FILE__ ));

    if ( !q.exec( "CREATE TABLE " + tableName + " (Word varchar(20))" ) ) {
        qDebug() << "Warning" << q.lastError();
    }

    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " values ('Albert')" ) );
    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " values ('Beehive')" ) );
    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " values ('Alimony')" ) );
    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " values ('Bohemian')" ) );
    QVERIFY_SQL( q, exec( "INSERT INTO " + tableName + " values ('AllStars')" ) );


    QString stmt = "SELECT * FROM " + tableName  +  " WHERE Word LIKE :name";
    QVERIFY_SQL(q,prepare(stmt));
    q.bindValue(":name", "A%");
    QVERIFY_SQL(q,exec());

    QVERIFY(q.isActive());
    QVERIFY(q.isSelect());
    QVERIFY(q.first());

    QSqlRecord rec = q.record();
    QCOMPARE(rec.field(0).value().toString(), QString("Albert"));
    QVERIFY(q.next());
    rec = q.record();
    QCOMPARE(rec.field(0).value().toString(), QString("Alimony"));
    QVERIFY(q.next());
    rec = q.record();
    QCOMPARE(rec.field(0).value().toString(),QString("AllStars"));

    q.exec("DROP TABLE " + tableName );
}

void tst_QSqlQuery::task_234422()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery query(db);
    QStringList m_airlines;
    QStringList m_countries;

    m_airlines << "Lufthansa" << "SAS" << "United" << "KLM" << "Aeroflot";
    m_countries << "DE" << "SE" << "US" << "NL" << "RU";

    const QString tableName(qTableName( "task_234422", __FILE__ ));

    QVERIFY_SQL(query,exec("CREATE TABLE " + tableName + " (id int primary key, "
                "name varchar(20), homecountry varchar(2))"));
    for (int i = 0; i < m_airlines.count(); ++i) {
        QVERIFY(query.exec(QString("INSERT INTO " + tableName + " values(%1, '%2', '%3')")
                    .arg(i).arg(m_airlines[i], m_countries[i])));
    }

    QVERIFY_SQL(query, exec("SELECT name FROM " + tableName));
    QVERIFY(query.isSelect());
    QVERIFY(query.first());
    QVERIFY(query.next());
    QCOMPARE(query.at(), 1);

    QSqlQuery query2(query);

    QVERIFY_SQL(query2,exec());
    QVERIFY(query2.first());
    QCOMPARE(query2.at(), 0);
    QCOMPARE(query.at(), 1);
}

#endif

void tst_QSqlQuery::task_233829()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q( db );
    const QString tableName(qTableName("task_233829", __FILE__));
    QVERIFY_SQL(q,exec("CREATE TABLE " + tableName  + "(dbl1 double precision,dbl2 double precision) without oids;"));

    QString queryString("INSERT INTO " + tableName +"(dbl1, dbl2) VALUES(?,?)");

    double k = 0.0;
    QVERIFY_SQL(q,prepare(queryString));
    q.bindValue(0,0.0 / k); // nan
    q.bindValue(1,0.0 / k); // nan
    QVERIFY_SQL(q,exec());
}

void tst_QSqlQuery::sqlServerReturn0()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if (!tst_Databases::isSqlServer( db ))
        QSKIP("SQL Server specific test", SkipSingle);

    const QString tableName(qTableName("test141895", __FILE__)), procName(qTableName("test141895_proc", __FILE__));
    QSqlQuery q( db );
    q.exec("DROP TABLE " + tableName);
    q.exec("DROP PROCEDURE " + procName);
    QVERIFY_SQL(q, exec("CREATE TABLE "+tableName+" (id integer)"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" (id) VALUES (1)"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" (id) VALUES (2)"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" (id) VALUES (2)"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" (id) VALUES (3)"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" (id) VALUES (1)"));
    QVERIFY_SQL(q, exec("CREATE PROCEDURE "+procName+
        " AS "
        "SELECT * FROM "+tableName+" WHERE ID = 2 "
        "RETURN 0"));

    QVERIFY_SQL(q, exec("{CALL "+procName+"}"));

    QVERIFY_SQL(q, next());
}

void tst_QSqlQuery::QTBUG_551()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    QSqlQuery q(db);
    const QString pkgname(qTableName("pkg", __FILE__));
    QVERIFY_SQL(q, exec("CREATE OR REPLACE PACKAGE "+pkgname+" IS \n\
            \n\
            TYPE IntType IS TABLE OF INTEGER      INDEX BY BINARY_INTEGER;\n\
            TYPE VCType  IS TABLE OF VARCHAR2(60) INDEX BY BINARY_INTEGER;\n\
            PROCEDURE P (Inp IN IntType,  Outp OUT VCType);\n\
            END "+pkgname+";"));

     QVERIFY_SQL(q, exec("CREATE OR REPLACE PACKAGE BODY "+pkgname+" IS\n\
            PROCEDURE P (Inp IN IntType,  Outp OUT VCType)\n\
            IS\n\
            BEGIN\n\
             Outp(1) := '1. Value is ' ||TO_CHAR(Inp(1));\n\
             Outp(2) := '2. Value is ' ||TO_CHAR(Inp(2));\n\
             Outp(3) := '3. Value is ' ||TO_CHAR(Inp(3));\n\
            END p;\n\
            END "+pkgname+";"));

    QVariantList inLst, outLst, res_outLst;

    q.prepare("begin "+pkgname+".p(:inp, :outp); end;");

    QString StVal;
    StVal.reserve(60);

    // loading arrays
    for (int Cnt=0; Cnt < 3; Cnt++) {
        inLst << Cnt;
        outLst << StVal;
    }

    q.bindValue(":inp", inLst);
    q.bindValue(":outp", outLst, QSql::Out);

    QVERIFY_SQL(q, execBatch(QSqlQuery::ValuesAsColumns) );
    res_outLst = qVariantValue<QVariantList>(q.boundValues()[":outp"]);
    QCOMPARE(res_outLst[0].toString(), QLatin1String("1. Value is 0"));
    QCOMPARE(res_outLst[1].toString(), QLatin1String("2. Value is 1"));
    QCOMPARE(res_outLst[2].toString(), QLatin1String("3. Value is 2"));
}

void tst_QSqlQuery::QTBUG_14132()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    QSqlQuery q(db);
    const QString procedureName(qTableName("procedure", __FILE__));
    QVERIFY_SQL(q, exec("CREATE OR REPLACE PROCEDURE "+ procedureName + " (outStr OUT varchar2)  \n\
                        is \n\
                        begin \n\
                        outStr := 'OUTSTRING'; \n\
                        end;"));
    QString placeholder = "XXXXXXXXX";
    QVERIFY(q.prepare("CALL "+procedureName+"(?)"));
    q.addBindValue(placeholder, QSql::Out);
    QVERIFY_SQL(q, exec());
    QCOMPARE(q.boundValue(0).toString(), QLatin1String("OUTSTRING"));
}

void tst_QSqlQuery::QTBUG_5251()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString timetest(qTableName("timetest", __FILE__));

    if (!db.driverName().startsWith( "QPSQL" )) return;

    QSqlQuery q(db);
    q.exec("DROP TABLE " + timetest);
    QVERIFY_SQL(q, exec("CREATE TABLE  " + timetest + " (t  TIME)"));
    QVERIFY_SQL(q, exec("INSERT INTO " + timetest +  " VALUES ('1:2:3.666')"));

    QSqlTableModel timetestModel(0,db);
    timetestModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    timetestModel.setTable(timetest);
    QVERIFY_SQL(timetestModel, select());

    QCOMPARE(timetestModel.record(0).field(0).value().toTime().toString("HH:mm:ss.zzz"), QString("01:02:03.666"));
    QVERIFY_SQL(timetestModel,setData(timetestModel.index(0, 0), QTime(0,12,34,500)));
    QCOMPARE(timetestModel.record(0).field(0).value().toTime().toString("HH:mm:ss.zzz"), QString("00:12:34.500"));
    QVERIFY_SQL(timetestModel, submitAll());
    QCOMPARE(timetestModel.record(0).field(0).value().toTime().toString("HH:mm:ss.zzz"), QString("00:12:34.500"));

    QVERIFY_SQL(q, exec("UPDATE " + timetest + " SET t = '0:11:22.33'"));
    QVERIFY_SQL(timetestModel, select());
    QCOMPARE(timetestModel.record(0).field(0).value().toTime().toString("HH:mm:ss.zzz"), QString("00:11:22.330"));

}

void tst_QSqlQuery::QTBUG_6421()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    QSqlQuery q(db);
    const QString tableName(qTableName("bug6421", __FILE__).toUpper());

    QVERIFY_SQL(q, exec("create table "+tableName+"(COL1 char(10), COL2 char(10), COL3 char(10))"));
    QVERIFY_SQL(q, exec("create index INDEX1 on "+tableName+" (COL1 desc)"));
    QVERIFY_SQL(q, exec("create index INDEX2 on "+tableName+" (COL2 desc)"));
    QVERIFY_SQL(q, exec("create index INDEX3 on "+tableName+" (COL3 desc)"));
    q.setForwardOnly(true);
    QVERIFY_SQL(q, exec("select COLUMN_EXPRESSION from ALL_IND_EXPRESSIONS where TABLE_NAME='"+tableName+"'"));
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toString(), QLatin1String("\"COL1\""));
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toString(), QLatin1String("\"COL2\""));
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toString(), QLatin1String("\"COL3\""));
}

void tst_QSqlQuery::QTBUG_6618()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if (!tst_Databases::isSqlServer( db ))
        QSKIP("SQL Server specific test", SkipSingle);

    QSqlQuery q(db);
    q.exec( "drop procedure " + qTableName( "tst_raiseError", __FILE__ ) );  //non-fatal
    QString errorString;
    for (int i=0;i<110;i++)
        errorString+="reallylong";
    errorString+=" error";
    QVERIFY_SQL( q, exec("create procedure " + qTableName( "tst_raiseError", __FILE__ ) + " as\n"
                         "begin\n"
                         "    raiserror('" + errorString + "', 16, 1)\n"
                         "end\n" ));
    q.exec( "{call " + qTableName( "tst_raiseError", __FILE__ ) + "}" );
    QVERIFY(q.lastError().text().contains(errorString));
}

void tst_QSqlQuery::QTBUG_6852()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if ( tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
        QSKIP( "Test requires MySQL >= 5.0", SkipSingle );

    QSqlQuery q(db);
    const QString tableName(qTableName("bug6852", __FILE__)), procName(qTableName("bug6852_proc", __FILE__));

    QVERIFY_SQL(q, exec("DROP PROCEDURE IF EXISTS "+procName));
    QVERIFY_SQL(q, exec("CREATE TABLE "+tableName+"(\n"
                        "MainKey INT NOT NULL,\n"
                        "OtherTextCol VARCHAR(45) NOT NULL,\n"
                        "PRIMARY KEY(`MainKey`))"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" VALUES(0, \"Disabled\")"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" VALUES(5, \"Error Only\")"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" VALUES(10, \"Enabled\")"));
    QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" VALUES(15, \"Always\")"));
    QVERIFY_SQL(q, exec("CREATE PROCEDURE "+procName+"()\n"
                        "READS SQL DATA\n"
                        "BEGIN\n"
                        "  SET @st = 'SELECT MainKey, OtherTextCol from "+tableName+"';\n"
                        "  PREPARE stmt from @st;\n"
                        "  EXECUTE stmt;\n"
                        "END;"));

    QVERIFY_SQL(q, exec("CALL "+procName+"()"));
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 0);
    QCOMPARE(q.value(1).toString(), QLatin1String("Disabled"));
}

void tst_QSqlQuery::QTBUG_5765()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if ( tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 1 ).toFloat()<4.1 )
        QSKIP( "Test requires MySQL >= 4.1", SkipSingle );

    QSqlQuery q(db);
    const QString tableName(qTableName("bug5765", __FILE__));

    QVERIFY_SQL(q, exec("CREATE TABLE "+tableName+"(testval TINYINT(1) DEFAULT 0)"));
    q.prepare("INSERT INTO "+tableName+" SET testval = :VALUE");
    q.bindValue(":VALUE", 1);
    QVERIFY_SQL(q, exec());
    q.bindValue(":VALUE", 12);
    QVERIFY_SQL(q, exec());
    q.bindValue(":VALUE", 123);
    QVERIFY_SQL(q, exec());
    QString sql="select testval from "+tableName;
    QVERIFY_SQL(q, exec(sql));
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 1);
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 12);
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 123);
    QVERIFY_SQL(q, prepare(sql));
    QVERIFY_SQL(q, exec());
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 1);
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 12);
    QVERIFY_SQL(q, next());
    QCOMPARE(q.value(0).toInt(), 123);
}

void tst_QSqlQuery::oraOCINumber()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    const QString qtest_oraOCINumber(qTableName("qtest_oraOCINumber", __FILE__));

    QSqlQuery q( db );
    q.setForwardOnly( true );
    QVERIFY_SQL( q, exec( "create table " + qtest_oraOCINumber +
                            " (col1 number(20), col2 number(20))" ) );
    QVERIFY(q.prepare("insert into " + qtest_oraOCINumber + " values (?, ?)"));
    QVariantList col1Values;
    QVariantList col2Values;
    col1Values << (qulonglong)(1)
               << (qulonglong)(0)
               << (qulonglong)(INT_MAX)
               << (qulonglong)(UINT_MAX)
               << (qulonglong)(LONG_MAX)
               << (qulonglong)(ULONG_MAX)
               << (qulonglong)(LLONG_MAX)
               << (qulonglong)(ULLONG_MAX);

    col2Values << (qlonglong)(1)
               << (qlonglong)(0)
               << (qlonglong)(-1)
               << (qlonglong)(LONG_MAX)
               << (qlonglong)(LONG_MIN)
               << (qlonglong)(ULONG_MAX)
               << (qlonglong)(LLONG_MAX)
               << (qlonglong)(LLONG_MIN);

    q.addBindValue(col1Values);
    q.addBindValue(col2Values);
    QVERIFY(q.execBatch());
    QString sqlStr = "select * from " + qtest_oraOCINumber +  " where col1 = :bindValue0 AND col2 = :bindValue1";
    QVERIFY(q.prepare(sqlStr));

    q.bindValue(":bindValue0", (qulonglong)(1), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(1), QSql::InOut);

    QVERIFY_SQL( q, exec() );
    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  qulonglong(1));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(1));

    q.bindValue(":bindValue0", (qulonglong)(0), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(0), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(0));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(0));

    q.bindValue(":bindValue0", (qulonglong)(INT_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(-1), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(INT_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(-1));

    q.bindValue(":bindValue0", (qulonglong)(UINT_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(LONG_MAX), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(UINT_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(LONG_MAX));

    q.bindValue(":bindValue0", (qulonglong)(LONG_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(LONG_MIN), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(LONG_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(LONG_MIN));

    q.bindValue(":bindValue0", (qulonglong)(ULONG_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(ULONG_MAX), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(ULONG_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(ULONG_MAX));

    q.bindValue(":bindValue0", (qulonglong)(LLONG_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(LLONG_MAX), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(LLONG_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(LLONG_MAX));

    q.bindValue(":bindValue0", (qulonglong)(ULLONG_MAX), QSql::InOut);
    q.bindValue(":bindValue1", (qlonglong)(LLONG_MIN), QSql::InOut);
    QVERIFY_SQL( q, exec() );

    QVERIFY( q.next() );
    QCOMPARE(q.boundValue( 0 ).toULongLong(),  (qulonglong)(ULLONG_MAX));
    QCOMPARE(q.boundValue( 1 ).toLongLong(),  (qlonglong)(LLONG_MIN));

}

void tst_QSqlQuery::sqlite_constraint()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );

    if (db.driverName() != QLatin1String("QSQLITE")) {
        QSKIP("Sqlite3 specific test", SkipSingle);
        return;
    }

    QSqlQuery q(db);
    const QString trigger(qTableName("test_constraint", __FILE__));

    QVERIFY_SQL(q, exec("CREATE TEMP TRIGGER "+trigger+" BEFORE DELETE ON "+qtest+
                        "\nFOR EACH ROW "
                        "\nBEGIN"
                        "\n  SELECT RAISE(ABORT, 'Raised Abort successfully');"
                        "\nEND;"
                        ));

    QVERIFY(!q.exec("DELETE FROM "+qtest));
    QCOMPARE(q.lastError().databaseText(), QLatin1String("Raised Abort successfully"));
}

#if 0
void tst_QSqlQuery::benchmark()
{
    QFETCH( QString, dbName );
    QSqlDatabase db = QSqlDatabase::database( dbName );
    CHECK_DATABASE( db );
    if ( tst_Databases::getMySqlVersion( db ).section( QChar('.'), 0, 0 ).toInt()<5 )
        QSKIP( "Test requires MySQL >= 5.0", SkipSingle );

    QSqlQuery q(db);
    const QString tableName(qTableName("benchmark", __FILE__));

    tst_Databases::safeDropTable( db, tableName );

    QVERIFY_SQL(q, exec("CREATE TABLE "+tableName+"(\n"
                        "MainKey INT NOT NULL,\n"
                        "OtherTextCol VARCHAR(45) NOT NULL,\n"
                        "PRIMARY KEY(`MainKey`))"));

    int i=1;

    QBENCHMARK {
        QVERIFY_SQL(q, exec("INSERT INTO "+tableName+" VALUES("+QString::number(i)+", \"Value"+QString::number(i)+"\")"));
        i++;
    }

    tst_Databases::safeDropTable( db, tableName );
}
#endif

QTEST_MAIN( tst_QSqlQuery )
#include "tst_qsqlquery.moc"
