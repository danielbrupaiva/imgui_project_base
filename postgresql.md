# PostgreSQL
[Link] https://www.postgresql.org/docs/current/installation.html

[Link] https://www.postgresql.org/download/linux/debian/

[Link] https://harshityadav95.medium.com/postgresql-in-windows-subsystem-for-linux-wsl-6dc751ac1ff3

    $ sudo sh -c 'echo "deb https://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list'
    $ wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
    $ sudo apt-get update
    $ sudo apt-get -y install postgresql-16
    
    postgresql-client-12        client libraries and client binaries
    postgresql-12               core database server
    libpq-dev                   libraries and headers for C language frontend development
    postgresql-server-dev-12    libraries and headers for C language backend development

## Build from source

    $ git clone -b REL_16_STABLE git://git.postgresql.org/git/postgresql.git
    $ cd postgresql
    
[HOST]

    $ mkdir build 
    $ cd build  
    $ ../configure
    $ make -j$(nproc)
    $ sudo make install
    
[TARGET]

    $ mkdir build build/install_aarch64
    $ cd build  
    
    Note: add to PATH the aarch64-beagle-linux-gnu 
    $ ../configure --host=aarch64-beagle-linux-gnu --prefix=$(pwd)/build/install 
    $ make -j$(nproc)
    $ sudo make install

~
    $ adduser postgres
    $ passwd postgres [1234]
    $ mkdir -p /usr/local/pgsql/data
    $ chown postgres /usr/local/pgsql/data
    $ su - postgres
    $ /usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data
    $ /usr/local/pgsql/bin/pg_ctl -D /usr/local/pgsql/data -l logfile start
    $ /usr/local/pgsql/bin/createdb test
    $ /usr/local/pgsql/bin/psql test
    
    $ sudo service postgresql start
    $ sudo service postgresql status
    $ sudo service postgresql stop
    
Access psql

    $ sudo -u postgres psql
    
Creating user

    $ sudo -u postgres createuser <username>

Giving the user a password

    $ sudo -u postgres psql
    $ psql=# alter user <username> with encrypted password '<password>';
             alter user imgui with encrypted password '1234';

Granting privileges on database

    $ psql=# grant all privileges on database <dbname> to <username> ; 

## PgAdmin

[Link] https://www.pgadmin.org/download/pgadmin-4-apt/

### Setup the repository

* Install the public key for the repository (if not done previously):
    
    $ curl -fsS https://www.pgadmin.org/static/packages_pgadmin_org.pub | sudo gpg --dearmor -o /usr/share/keyrings/packages-pgadmin-org.gpg

* Create the repository configuration file:
    
    $ sudo sh -c 'echo "deb [signed-by=/usr/share/keyrings/packages-pgadmin-org.gpg] https://ftp.postgresql.org/pub/pgadmin/pgadmin4/apt/$(lsb_release -cs) pgadmin4 main" > /etc/apt/sources.list.d/pgadmin4.list && apt update'

* Install for both desktop and web modes:

    $ sudo apt install pgadmin4

* Install for desktop mode only:

    $ sudo apt install pgadmin4-desktop

* Install for web mode only: 
    
    $ sudo apt install pgadmin4-web 

* Configure the webserver, if you installed pgadmin4-web:

    $ sudo /usr/pgadmin4/bin/setup-web.sh
    
