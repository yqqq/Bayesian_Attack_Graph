import xml.etree.ElementTree as etree

def print_node(node):
    print "====================================="
    for key,value in node.items():
      print "%s:%s" % (key, value)   
    for subnode in node.getchildren():
      print "%s:%s" % (subnode.tag, subnode.text)
'''
   find_host_info function was defined to find each host's infomation
   We can use this info to represent the basic info of host      
'''

def find_host_info(node):
    #the node must be host(Process)
    #print "host_info_find_successfully!"
    host_info=node.findall("HostProperties")
    return host_info

def find_atomic_attack(node):
    #This place the node must be host(Process)
    #print "atomic_info_find_successfully"
    atomic_attack=node.findall("ReportItem")
    return atomic_attack
    
def get_attack_description(node):
    attack_discription=node.findall("pluginName")
    print attack_discription[0].text
    #attack_discription[0].text is the return of the attack description

def get_cvss_score(node):
    cvss_score=node.findall("cvss_temporal_score")
    print cvss_score[0].text
    #cvss_score[0].text is the score of the atomic attack 

def get_risk_level(node):
    risk_level=node.findall("risk_factor")
    print risk_level[0].text
    #risk_level[0].text is the risk level of the attack

def get_attack_family(node):
    attack_family=node.findall("pluginFamily")
    print attack_family[0].text
    #risk_level[0].text is the risk level of the attack
     
   
if __name__ == '__main__':
    tree=etree.parse("ciso.xml")
    root=tree.getroot()
    #print root
    host_set=root.findall("Process")
    for host in host_set:
	#print all the host info
    	host_info_set=find_host_info(host)
	for host_info in host_info_set:
		print_node(host_info)
        atomic_attack_set=find_atomic_attack(host)
	for  atomic_attack in atomic_attack_set:
		get_attack_description(atomic_attack)
		get_cvss_score(atomic_attack)
		get_risk_level(atomic_attack)
		
		
	
