import numpy as np

# 读入 n, d_model, d_k, d_v, causal
n, d_model, d_k, d_v, causal  = map(int, input().split())

data_count = n * d_model + d_model * d_k + d_model * d_k + d_model * d_v
data = []
while len(data) < data_count:
    data += list(map(float, input().split()))

p = 0
X = np.array(data[p : p + n * d_model]).reshape(n, d_model)
p += n * d_model

W_Q = np.array(data[p : p + d_model * d_k]).reshape(d_model, d_k)
p += d_model * d_k

W_K = np.array(data[p : p + d_model * d_k]).reshape(d_model, d_k)
p += d_model * d_k

W_V = np.array(data[p : p + d_model * d_v]).reshape(d_model, d_v)

# projection
Q = X @ W_Q
K = X @ W_K
V = X @ W_V

# S
S = Q @ K.T / np.sqrt(d_k)

# mask (只有causal为1才有效)
mask = np.zeros((n, n))
if causal == 1:
    for i in range(n):
        for j in range(i + 1, n):
            mask[i, j] = -np.inf

# merge mask
temp = S + mask

# softmax -> A
temp = temp - temp.max(axis = 1, keepdims = True)
exp = np.exp(temp)
A = exp / exp.sum(axis = 1, keepdims = True)

# O
O = A @ V

# print
print(*Q.ravel())
print(*K.ravel())
print(*V.ravel())
print(*S.ravel())
print(*A.ravel())
print(*O.ravel())