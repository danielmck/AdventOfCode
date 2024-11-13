from urllib.request import urlretrieve, urlopen, Request

url = 'https://adventofcode.com/2022/day/1/'
# url = 'https://google.com'
# request = Request(url)
# response = urlopen(request)
# response = response.read()
# urlretrieve(url, 'day1_input.txt')

import urllib2
file("my_file.txt", "w").write(urllib2.urlopen(url).read())