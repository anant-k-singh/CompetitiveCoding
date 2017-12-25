import re
emails = []
n = int(input())
for _ in range(n):
	sentence = input().split()
	# sentence = re.split(',|;| |\n',input())
	# sentence = re.split(' |\n',input())
	for word in sentence:
		match = re.match('^[_A-Za-z0-9]+(\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]+(\.[A-Za-z0-9-]+)*(\.[A-Za-z]{2,5})', word)
		if match != None:
			emails.append(match.group(0))
emailset = set(emails)
emails = sorted(emailset)
print (';'.join(emails))
# print("--------------")
# for email in emails:
# 	print (email)