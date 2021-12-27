import os
channels =[
    ('mt', 'process_trees_lt_fr'),
    ('et', 'process_trees_lt_fr'),
    ('tt', 'process_trees_tt'),
    ('me', 'process_trees_em'),
    ('em', 'process_trees_em')
]
year = ['2016','2017','2018']
for yr in year:
    for ch in channels:
        print './{} -d Output/tree/CADI_{}_{}_v1/NN_nominal  --suf test2 -v m_sv -b 30 0 300'.format(ch[1],ch[0],yr)
        os.system('./{} -d Output/trees/CADI_{}_{}_v1/NN_nominal  --suf test2 -v m_sv -b 30 0 300'.format(ch[1],ch[0],yr))
        
        
