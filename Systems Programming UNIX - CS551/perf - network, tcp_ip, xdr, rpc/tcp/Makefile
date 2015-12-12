all: manage report compute rpc
rpc: mdata.x
	rpcgen mdata.x
manage: manage.c
	cc manage.c mdata_xdr.c -Wall -o manage
report: report.c
	cc report.c mdata_xdr.c -Wall -o report
compute: compute.c
	cc compute.c mdata_xdr.c -Wall -pthread -o compute
