def gen_parents(vertices):
    parents = []
    for i,v in enumerate(vertices):
        parents.append([])
    for i,v in enumerate(vertices):
        c0 = v[0]
        c1 = v[1]
        parents[c0].append(i)
        parents[c1].append(i)
    return parents
    
def gen_children(vertices):
    children = []
    for i,v in enumerate(vertices):
        children.append([v[0], v[1]])
    return children
    
def do(parents, children, masses):
    loop_l = 0
    s = {0}
    l = [0]
    i = [-1]
    while(True):
#         print('state')
#         print(l)
#         print(s)
#         print(i)
        if not l:
            break
        last = l[-1]
        i[-1] += 1
        ind = i[-1]
        last_p = parents[last]
        if ind >= len(last_p):
            # backward
            s.remove(last)
            removed = l.pop(-1)
            i.pop(-1)
            fac = masses[removed]
            for child in children[removed]:
                masses[child] += fac
            continue
        candidate = last_p[ind]
        if candidate in s:
#             # sideways
#             i[-1] += 1
#             continue
            # handle zero mass
            if candidate == 0:
                loop_l += 1
                if loop_l > 1:
                    return -1
                else:
                    # sideways
                    continue
            else:
                return -1
        # forward
        s.add(candidate)
        l.append(candidate)
        i.append(-1)
    return masses[0]
        
        
        
            
        
    
        
    
T = int(input())
for t in range(T):
    M = int(input())
    vertices = []
    masses = []
    for m in range(M):
        l = input().split()
        vertices.append((int(l[0])-1, int(l[1])-1))
    l = input().split()
    
    for m in range(M):
        masses.append(int(l[m]))
        
    children = gen_children(vertices)
    parents = gen_parents(vertices)
    
    print('sdfasdf')
    print(parents, children, masses)
    sol = do(parents, children, masses)
    print(sol)


        
    
    
        