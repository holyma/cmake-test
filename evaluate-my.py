import numpy as np
import torch
from torch.autograd import Variable
import utils
import model.net as net
# 1.词典读取

vocab_path = "/root/git/cs230-code-examples/pytorch/nlp/data/small/words.txt"
tag_path = "/root/git/cs230-code-examples/pytorch/nlp/data/small/tags.txt"

vocabs,tags,anti_tags = {},{},{}
with open(vocab_path)as f:
    for i,l in enumerate(f.read().splitlines()):
        vocabs[l] = i
with open(tag_path)as f:
    for i,l in enumerate(f.read().splitlines()):
        tags[l] = i
        anti_tags[i] = l

unk_ind,pad_ind = vocabs['UNK'],vocabs['<pad>']

# 2.句子转换为ID
# sentences = "The U.S. State Department and the European parliament also voiced concern ."
# label = "O B-org I-org I-org O O O O O O O O"
sentences = "They marched from the Houses of Parliament to a rally in Hyde Park ."
label = "O O O O O O O O O O O B-geo I-geo O"
sentences_ids = [vocabs[w] if w in vocabs.keys() else unk_ind for w in sentences.split(" ")]
label_ids = [tags[w]  for w in label.split(" ")]

assert len(label_ids) == len(sentences_ids)

# 转换为tensor
# 空数组(pad)
batch_sentences = pad_ind * np.ones((1,100))
batch_label = -1 * np.ones((1,100))
# 数据->空数组 = paded ndarray
batch_sentences[0][:len(sentences_ids)] = sentences_ids
batch_label[0][:len(label_ids)] = label_ids
# paded ndarray -> tensor
batch_sentences,batch_label = torch.LongTensor(batch_sentences),torch.LongTensor(batch_label)
# batch_data, batch_labels = Variable(batch_data), Variable(batch_labels)

# 送入模型
json_path = "/root/git/cs230-code-examples/pytorch/nlp/experiments/base_model/params.json"
model_path = "/root/git/cs230-code-examples/pytorch/nlp/experiments/base_model/best.pth.tar"
params = utils.Params(json_path)
params.cuda = False# torch.cuda.is_available()   
params.unk_word = "UNK"
params.vocab_size = 368
params.number_of_tags = 9
params.pad_tag = "O"
params.pad_word = "<pad>"

model = net.Net(params).cuda() if params.cuda else net.Net(params)
utils.load_checkpoint(model_path, model)
model.eval()
out_batch = model(batch_sentences) # [maxlen*bsz, tag_size]

# 结果tensor -> 文本
outputs = torch.argmax(out_batch, axis=1) # 输出最大值的下标,[maxlen*baz]
outputs = outputs.numpy()
output_label = [  anti_tags[i] for i in outputs][:len(sentences_ids)]

print(output_label)
print(label)


