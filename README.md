# Soteria Pass Server
Password Manager that uses a client/server architecture to store encrypted passwords remotely. This portion is the backend server

## Dependencies
* [gRpc](http://www.grpc.io/)
* [Protocol Buffers](https://developers.google.com/protocol-buffers/)
* [OpenSSL](https://www.openssl.org/)
* [Sqlite3 (available in repos)](https://sqlite.org/)

## Installation
* Install all of the dependencies (documentation to come in the future)

### gRpc and Protocol Buffers
```sh
 $ git clone -b $(curl -L http://grpc.io/release) https://github.com/grpc/grpc
 $ cd grpc
 $ git submodule update --init
 $ make
 $ [sudo] make install
```

### Soteria Pass server

#### Build from sources
The first part is to build from sources

```sh
 $ git clone https://github.com/soteriapass/server
 $ cd src/
 $ make
 $ [sudo] make install
```

#### Key and certificate creation using easy-rsa

After this, we will need to configure the server. We will need to generate encryption keys and server certificates. We will accompish this using easy-rsa.

```sh
 $ git clone -b release/2.x https://github.com/soteriapass/easy-rsa
 $ cd easy-rsa/easy-rsa/2.0/
```

#### Variable configuration (optional)

!No longer valid with easy-rsa 3

This step is optional, but it does allow you to configure the default values for the certificate creation to ensure that they are consistent.

```sh
 $ vim ./vars
```

We want to modify all of the "KEY\_" variables, which should be located at the bottom of the file. The variables names are easy enough to understand. Once the "vars" are all completed, you should have something resembling this:

```sh
export KEY_COUNTRY="US"
export KEY_PROVINCE="NY"
export KEY_CITY="New York"
export KEY_ORG="Organization Name"
export KEY_EMAIL="administrator@example.com"
export KEY_CN=droplet.example.com
export KEY_NAME=server
export KEY_OU=server
```

#### Certificate Authority setup
We can now build our certificate authority (CA for short), based on the information provided in the vars file

```sh
 $ source ./vars
 $ ./clean-all
 $ ./build-ca
```

#### Create the certificate

```sh
 $ ./build-key-server server
 $ ./build-dh
```

#### Create the keys for the different services

```sh
 $ ./build-key user_server
```

#### Copy everything to a common directory

```sh
 $ [sudo] mkdir /etc/pswmgr/
 $ [sudo] mkdir /etc/pswmgr/keys/
 $ cd keys/
 $ [sudo] cp ca.crt server.crt server.key user_server.crt user_server.key ca.crt /etc/pswmgr/keys
```

#### Generate encryption keys

TO COMPLETE

## Supported platforms

The current supported OS is Linux. Window support planned for the future.

## Cryptography Notice

This distribution includes cryptographic software. The country in which you currently reside may have restrictions on the import, possession, use, and/or re-export to another country, of encryption software. BEFORE using any encryption software, please check your country's laws, regulations and policies concerning the import, possession, or use, and re-export of encryption software, to see if this is permitted. See [http://www.wassenaar.org/](http://www.wassenaar.org/) for more information.

## License
The main license for this project is the GPLv3 - [https://github.com/devgeeks/Encryptr/blob/master/LICENSE](https://github.com/devgeeks/Encryptr/blob/master/LICENSE)

Certain parts of this distribution is licensed under the Apache License [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)
